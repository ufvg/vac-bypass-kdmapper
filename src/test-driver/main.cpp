#include "includes.hpp"

std::unique_ptr<IVACDriverManager> g_VACDriverManager = nullptr;

void RegisterKnownProcesses()
{
    struct ProcessInfo
    {
        const wchar_t *name;
        INT role;
    };

    ProcessInfo procs[] = {{L"steam.exe", 1}, {L"steamservice.exe", 2}, {L"cs2.exe", 3}};

    for (const auto &proc : procs)
    {
        ULONG pid = Utils::GetProcessIdByName(proc.name);
        if (pid != (ULONG)-1)
        {
            std::wcout << L"[+] Found " << proc.name << L" (PID: " << std::dec << pid << L"), registering with driver."
                       << std::endl;
            NTSTATUS status =
                g_VACDriverManager->RegisterProcess(reinterpret_cast<HANDLE>((ULONG_PTR)pid), TRUE, proc.role);

            // STATUS_ALREADY_REGISTERED is not a critical failure
            if (!NT_SUCCESS(status) && status != STATUS_ALREADY_REGISTERED)
            {
                std::wcerr << L"Error: Failed to register " << proc.name << L", status 0x" << std::hex << std::uppercase
                           << std::setw(8) << std::setfill(L'0') << status << std::endl;
            }
        }
    }
}

void UnregisterKnownProcesses()
{
    struct ProcessInfo
    {
        const wchar_t *name;
        INT role;
    };

    ProcessInfo procs[] = {{L"steam.exe", 1}, {L"steamservice.exe", 2}, {L"cs2.exe", 3}};

    std::wcout << L"[*] Unregistering known processes from driver..." << std::endl;
    for (const auto &proc : procs)
    {
        ULONG pid = Utils::GetProcessIdByName(proc.name);
        if (pid != (ULONG)-1)
        {
            g_VACDriverManager->RegisterProcess(reinterpret_cast<HANDLE>((ULONG_PTR)pid), FALSE, proc.role);
        }
    }
}

int handleTest()
{
    ULONG processId = Utils::GetProcessIdByName(L"cs2.exe");
    if (processId == -1)
    {
        std::wcerr << L"Error: cs2.exe not found!" << std::endl;
        return EXIT_FAILURE;
    }

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (!processHandle || processHandle == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Error: Could not open process, error " << GetLastError() << std::endl;
        return EXIT_FAILURE;
    }

    HMODULE hmodClient = Utils::GetProcessModule(processId, L"client.dll");
    if (!hmodClient)
    {
        std::wcerr << L"Error: client.dll not found!" << std::endl;
        return EXIT_FAILURE;
    }

    std::wcout << L"client.dll = " << std::hex << std::uppercase << std::setw(16) << std::setfill(L'0') << hmodClient
               << std::endl;

    SIZE_T bytesRead = 0;

    IMAGE_DOS_HEADER dosh{};
    if (!ReadProcessMemory(processHandle, hmodClient, &dosh, sizeof(dosh), &bytesRead))
    {
        std::wcerr << L"Error: Could not read file MZ header, error " << GetLastError() << std::endl;
        return EXIT_FAILURE;
    }

    IMAGE_NT_HEADERS nth{};
    if (!ReadProcessMemory(processHandle, reinterpret_cast<PUCHAR>(hmodClient) + dosh.e_lfanew, &nth, sizeof(nth),
                           &bytesRead))
    {
        std::wcerr << L"Error: Could not open read file PE header, error " << GetLastError() << std::endl;
        return EXIT_FAILURE;
    }

    PUCHAR codeStart = reinterpret_cast<PUCHAR>(hmodClient) + nth.OptionalHeader.BaseOfCode;
    PUCHAR codeEnd = codeStart + nth.OptionalHeader.SizeOfCode;

    std::wcout << L"CodeStart = " << std::hex << std::uppercase << std::setw(16) << std::setfill(L'0') << codeStart
               << std::endl;

    std::wcout << L"CodeEnd = " << std::hex << std::uppercase << std::setw(16) << std::setfill(L'0') << codeEnd
               << std::endl;

    std::wcout << L"Reading non overlapping region" << std::endl;
    {
        auto buffer = new UCHAR[nth.OptionalHeader.SizeOfCode];

        if (!ReadProcessMemory(processHandle, codeStart, buffer, nth.OptionalHeader.SizeOfCode, &bytesRead))
        {
            std::wcerr << L"Error: Could not read module memory, error " << GetLastError() << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::wcout << L"Reading overlapping region 1" << std::endl;
    {
        auto buffer = new UCHAR[nth.OptionalHeader.SizeOfCode];

        if (!ReadProcessMemory(processHandle, codeStart + 0x1000, buffer, nth.OptionalHeader.SizeOfCode - 0x1000,
                               &bytesRead))
        {
            std::wcerr << L"Error: Could not read module memory, error " << GetLastError() << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::wcout << L"Reading overlapping region 2" << std::endl;
    {
        auto buffer = new UCHAR[nth.OptionalHeader.SizeOfCode];

        if (!ReadProcessMemory(processHandle, codeStart - 0x1000, buffer, nth.OptionalHeader.SizeOfCode, &bytesRead))
        {
            std::wcerr << L"Error: Could not read module memory, error " << GetLastError() << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::wcout << L"Reading overlapping region 3" << std::endl;
    {
        auto buffer = new UCHAR[0x2000];

        if (!ReadProcessMemory(processHandle, codeEnd - 0x1000, buffer, 0x2000, &bytesRead))
        {
            std::wcerr << L"Error: Could not read module memory, error " << GetLastError() << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int handleBypass(const std::vector<std::wstring> &args)
{
    NTSTATUS status;
    bool disableCalled = false;

    // FIX: Original loop started at 3, skipping the first argument. Changed to 2.
    for (size_t i = 2; i < args.size(); ++i)
    {
        if (args[i].find(L"/enable") != std::string::npos)
        {
            status = g_VACDriverManager->EnableBypass();
            if (!NT_SUCCESS(status))
            {
                std::wcerr << L"Error: EnableBypass returned 0x" << std::hex << std::uppercase << std::setw(8)
                           << std::setfill(L'0') << status << std::endl;
                return EXIT_FAILURE;
            }

            std::wcout << L"[!] Successfully enabled bypass!" << std::endl;
        }
        else if (args[i].find(L"/disable") != std::string::npos)
        {
            disableCalled = true;
            status = g_VACDriverManager->DisableBypass();
            if (!NT_SUCCESS(status))
            {
                std::wcerr << L"Error: DisableBypass returned 0x" << std::hex << std::uppercase << std::setw(8)
                           << std::setfill(L'0') << status << std::endl;
                return EXIT_FAILURE;
            }

            std::wcout << L"[!] Successfully disabled bypass!" << std::endl;
        }
        else
        {
            std::wcerr << L"Error: Unrecognized command: " << args[i] << std::endl;
            return EXIT_FAILURE;
        }
    }

    // When disabling the bypass, unregister processes to trigger the driver's internal cleanup
    if (disableCalled)
    {
        UnregisterKnownProcesses();
    }
    return EXIT_SUCCESS;
}

int handleInjectDll(const std::vector<std::wstring> &args)
{
    const std::wstring dllPath = args[2];

    if (!std::filesystem::exists(dllPath))
    {
        std::wcerr << L"Error: File " << dllPath << L" not found!" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<uint8_t> imageBuffer{};

    try
    {
        std::ifstream file(dllPath, std::ios::binary | std::ios::ate);

        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        imageBuffer = std::vector<uint8_t>(fileSize);

        file.read(reinterpret_cast<char *>(imageBuffer.data()), fileSize);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    const NTSTATUS status = g_VACDriverManager->InjectDll(imageBuffer);
    if (!NT_SUCCESS(status))
    {
        std::wcerr << L"Error: InjectDll returned 0x" << std::hex << std::uppercase << std::setw(8)
                   << std::setfill(L'0') << status << std::endl;
        return EXIT_FAILURE;
    }

    std::wcout << L"[!] Successfully injected DLL!" << std::endl;

    return EXIT_SUCCESS;
}

int wmain(int argc, const wchar_t **argv)
{
    SetConsoleTitle(L"Test Driver");

    if (argc < 2)
    {
        printf(R"(Usage: test-driver.exe <operation> <...>
Operations:
    
    test        -   Run bypass test
    bypass      -   Control bypass status
    inject-dll  -   Inject DLL in game


Options:

    inject-dll  <dll-path> <...>

        No additional params.

    bypass
        
        /disable  Disable bypass
        /enable   Enable bypass
)");
        return 1;
    }

    std::vector<std::wstring> args(argv, argv + argc);
    std::wstring operation = args[1];

    try
    {
        g_VACDriverManager = std::make_unique<IVACDriverManager>();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    bool isDisableBypass =
        (operation == L"bypass" && args.size() >= 3 && args[2].find(L"/disable") != std::string::npos);

    // Register known processes with the driver so it knows which PIDs to hook/spoof for.
    // This replaces the kernel-mode PsSetCreateProcessNotifyRoutineEx callback.
    if (!isDisableBypass)
    {
        RegisterKnownProcesses();
    }

    // Handle operations
    //
    if (operation == L"test")
    {
        return handleTest();
    }
    else if (operation == L"bypass")
    {
        if (args.size() < 3)
        {
            std::cerr << "Error: 'bypass' requires at least one argument: /disable or /enable" << std::endl;
            return EXIT_FAILURE;
        }
        return handleBypass(args);
    }
    else if (operation == L"inject-dll")
    {
        if (args.size() < 3)
        {
            std::cerr << "Error: 'inject-dll' requires at least one argument: <dll-path>" << std::endl;
            return EXIT_FAILURE;
        }
        return handleInjectDll(args);
    }

    std::wcerr << L"Error: Unknown operation " << operation << std::endl;
    return EXIT_FAILURE;
}