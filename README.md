# VAC kernel-mode bypass

# How it works

VAC is loaded in *SteamService.exe* process (*Steam.exe* will be the process loading it if being ran as administrator instead). 

Basically the anti-cheat is fully external, meaning that it makes use of syscalls like **NtReadVirtualMemory** in order to read game memory and perform some checks. 
Because it's designed like that we can simply intercept those syscalls in a higher level (ring-0) and spoof whatever is being checked/scanned.

*Steam.exe*, *SteamService.exe* and *cs2.exe* are placed into a thread-safe list, this list is used for reference in hooks so we know which process is calling the syscall and which process is requested to be queried from.

Any allocation done by the manual map is also stored in a thread-safe list which is used as reference in hooks in order to spoof any query from **NtReadVirtualMemory** or **NtQueryVirtualMemory**, thus breaking any signature/heuristic check possible.

I place a hook in  **NtMapViewOfSection** so i can intercept any module being loaded as soon as possible, meaning i can create a copy of the module, relocate it and later on i can spoof any VAC query using the copy.

```
static wchar_t *g_BackupModulesList[] = {L"\\bin\\win64\\client.dll",           L"\\bin\\win64\\engine.dll",
                                         L"\\bin\\win64\\materialsystem2.dll",  L"\\bin\\win64\\inputsystem.dll",
                                         L"\\bin\\win64\\rendersystemdx11.dll", L"\\bin\\win64\\rendersystemvulkan.dll",
                                         L"\\bin\\win64\\inputsystem.dll",      L"\\bin\\win64\\scenesystem.dll"};
```

The list is currently hardcoded, there's no need to copy every single loaded module from the game, only the ones you're going to patch.

Because Steam and VAC also makes some system queries like checking if system is in Test or Debug mode we also intercept **NtQuerySystemInformation**, ultimately defeating anything that can lower the trust-factor system.

*In Debug mode there are CRC32 checks used to ensure the spoofed results are consistent, that basically means we're ensuring VAC is really getting what it "expected".*

## Usage

```
Usage: test-driver.exe <operation> <...>
Operations:
    
    test        -   Run bypass test
    bypass      -   Control bypass status
    inject-dll  -   Inject DLL in game


Options:

    inject-dll  <dll-path>

        No additional params.

    bypass
        
        /disable  Disable bypass
        /enable   Enable bypass
```
