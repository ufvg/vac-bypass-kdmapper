#pragma once

class IVACDriverManager
{
  private:
    HANDLE deviceHandle = INVALID_HANDLE_VALUE;

    template <class T> NTSTATUS SendIoctl(_In_ T *request)
    {
        const ULONG bufferSize = sizeof(T);

        IO_STATUS_BLOCK iosb{};
        const NTSTATUS status = NtDeviceIoControlFile(this->deviceHandle, nullptr, nullptr, nullptr, &iosb,
                                                      IOCTL_VAC_REQUEST, request, bufferSize, request, bufferSize);
        if (!NT_SUCCESS(status))
        {
            std::wcerr << L"Error: NtDeviceIoControlFile returned 0x" << std::hex << std::uppercase << std::setw(8)
                       << std::setfill(L'0') << status << std::endl;

            request->SetStatus(status);
        }
        return request->Status;
    }

  public:
    IVACDriverManager()
    {
        this->deviceHandle = CreateFile(L"." VAC_DEVICE_GUID, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
                                        FILE_ATTRIBUTE_NORMAL, NULL);
        if (!this->deviceHandle || this->deviceHandle == INVALID_HANDLE_VALUE)
        {
            throw std::runtime_error("Failed to open device. Error: " + std::to_string(GetLastError()));
        }
    }

    ~IVACDriverManager()
    {
        if (this->deviceHandle && this->deviceHandle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(this->deviceHandle);
            this->deviceHandle = INVALID_HANDLE_VALUE;
        }
    }

    NTSTATUS DisableBypass()
    {
        auto request = new Comms::DRIVER_REQUEST_DISABLE_BYPASS();
        NTSTATUS status = SendIoctl(request);
        delete request;
        return status;
    }

    NTSTATUS EnableBypass()
    {
        auto request = new Comms::DRIVER_REQUEST_ENABLE_BYPASS();
        NTSTATUS status = SendIoctl(request);
        delete request;
        return status;
    }

    NTSTATUS InjectDll(_In_ std::vector<uint8_t> &imageBuffer)
    {
        auto request = new Comms::DRIVER_REQUEST_INJECT(reinterpret_cast<PVOID>(imageBuffer.data()),
                                                        static_cast<ULONG>(imageBuffer.size()));
        NTSTATUS status = SendIoctl(request);
        delete request;
        return status;
    }

    NTSTATUS RegisterProcess(HANDLE processId, BOOLEAN add, INT role)
    {
        auto request = new Comms::DRIVER_REQUEST_REGISTER_PROCESS(processId, add, role);
        NTSTATUS status = SendIoctl(request);
        delete request;
        return status;
    }
};