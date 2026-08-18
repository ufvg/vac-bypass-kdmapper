#pragma once

#define VAC_DEVICE_GUID L"{272C5244-95ED-402D-B511-CE6511F96DFE}"

#define IOCTL_VAC_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0, METHOD_BUFFERED, FILE_ANY_ACCESS)

namespace Comms
{
enum class EDriverCommunicationRequest : int
{
    Invalid,
    EnableBypass,
    DisableBypass,
    InjectDll,
    Max
};

static constexpr int DRIVER_REQUEST_MAGIC = 'Bcta';

typedef struct _DRIVER_REQUEST_HEADER
{
    int Magic = DRIVER_REQUEST_MAGIC;
    EDriverCommunicationRequest Request = EDriverCommunicationRequest::Invalid;
    NTSTATUS Status = STATUS_INVALID_DEVICE_REQUEST;

    bool IsValid(void) const
    {
        return (this->Magic == DRIVER_REQUEST_MAGIC && (this->Request > EDriverCommunicationRequest::Invalid &&
                                                        this->Request < EDriverCommunicationRequest::Max));
    }

    void SetStatus(_In_ const NTSTATUS status)
    {
        this->Status = status;
    }

} DRIVER_REQUEST_HEADER, *PDRIVER_REQUEST_HEADER;

typedef struct _DRIVER_REQUEST_INJECT : DRIVER_REQUEST_HEADER
{
    PVOID ImageBase;
    ULONG ImageSize;

    _DRIVER_REQUEST_INJECT(_In_ PVOID imageBase, _In_ ULONG imageSize) : ImageBase(imageBase), ImageSize(imageSize)
    {
        this->Request = EDriverCommunicationRequest::InjectDll;
    }

} DRIVER_REQUEST_INJECT, *PDRIVER_REQUEST_INJECT;

typedef struct _DRIVER_REQUEST_DISABLE_BYPASS : DRIVER_REQUEST_HEADER
{
    _DRIVER_REQUEST_DISABLE_BYPASS()
    {
        this->Request = EDriverCommunicationRequest::DisableBypass;
    }

} DRIVER_REQUEST_DISABLE_BYPASS, *PDRIVER_REQUEST_DISABLE_BYPASS;

typedef struct _DRIVER_REQUEST_ENABLE_BYPASS : DRIVER_REQUEST_HEADER
{
    _DRIVER_REQUEST_ENABLE_BYPASS()
    {
        this->Request = EDriverCommunicationRequest::EnableBypass;
    }

} DRIVER_REQUEST_ENABLE_BYPASS, *PDRIVER_REQUEST_ENABLE_BYPASS;

} // namespace Comms