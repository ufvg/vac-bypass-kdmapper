#pragma once

#include "..\shared\shared.hpp"

#include <windows.h>
#include <vector>
#include <iostream>
#include <iomanip>

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

#ifndef STATUS_PROCEDURE_NOT_FOUND
#define STATUS_PROCEDURE_NOT_FOUND ((NTSTATUS)0xC000007AL)
#endif

class IVACDriverManager
{
  private:
    using NtReadVirtualMemory_t = NTSTATUS(NTAPI *)(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer,
                                                    SIZE_T NumberOfBytesToRead, SIZE_T *NumberOfBytesRead);

    NtReadVirtualMemory_t m_NtReadVirtualMemory = nullptr;

    bool ResolveImports()
    {
        if (m_NtReadVirtualMemory)
        {
            return true;
        }

        HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
        if (!ntdll)
        {
            ntdll = LoadLibraryW(L"ntdll.dll");
        }

        if (!ntdll)
        {
            return false;
        }

        m_NtReadVirtualMemory = reinterpret_cast<NtReadVirtualMemory_t>(GetProcAddress(ntdll, "NtReadVirtualMemory"));

        return m_NtReadVirtualMemory != nullptr;
    }

    template <class T> NTSTATUS SendIoctl(_In_ T *request)
    {
        if (!ResolveImports())
        {
            std::wcerr << L"Error: failed to resolve NtReadVirtualMemory from ntdll.dll" << std::endl;
            request->SetStatus(STATUS_PROCEDURE_NOT_FOUND);
            return request->Status;
        }

        SIZE_T bytesRead = 0;

        const NTSTATUS status = m_NtReadVirtualMemory(VAC_COMM_HANDLE, request, request, sizeof(T), &bytesRead);

        if (!NT_SUCCESS(status))
        {
            std::wcerr << L"Error: driver communication failed, NtReadVirtualMemory returned 0x" << std::hex
                       << std::uppercase << std::setw(8) << std::setfill(L'0') << status << std::dec << std::nouppercase
                       << std::endl;

            request->SetStatus(status);
        }

        return request->Status;
    }

  public:
    IVACDriverManager()
    {
        ResolveImports();
    }

    ~IVACDriverManager() = default;

    NTSTATUS DisableBypass()
    {
        Comms::DRIVER_REQUEST_DISABLE_BYPASS request;
        return SendIoctl(&request);
    }

    NTSTATUS EnableBypass()
    {
        Comms::DRIVER_REQUEST_ENABLE_BYPASS request;
        return SendIoctl(&request);
    }

    NTSTATUS InjectDll(_In_ std::vector<uint8_t> &imageBuffer)
    {
        Comms::DRIVER_REQUEST_INJECT request(reinterpret_cast<PVOID>(imageBuffer.data()),
                                             static_cast<ULONG>(imageBuffer.size()));

        return SendIoctl(&request);
    }

    NTSTATUS RegisterProcess(HANDLE processId, BOOLEAN add, INT role)
    {
        Comms::DRIVER_REQUEST_REGISTER_PROCESS request(processId, add, role);
        return SendIoctl(&request);
    }
};