#pragma once

namespace SyscallHook
{
inline Threads::KERNEL_THREAD g_SyscallHookThread = {};

#if (SYSCALL_HOOK_TYPE == SYSCALL_HOOK_INFINITY_HOOK)
typedef VOID(__fastcall *SSDT_CALLBACK)(ULONG, PVOID *);

inline SSDT_CALLBACK g_SsdtCallback = NULL;
inline PVOID g_SyscallTableAddress = nullptr;

inline PVOID *g_GetCpuClock = nullptr;
inline PVOID *g_HvlpReferenceTscPage = nullptr;
inline PVOID *g_HvlGetQpcBias = nullptr;

inline PVOID g_HvlGetQpcBiasOriginal = nullptr;
inline PVOID g_GetCpuClockOriginal = nullptr;

ULONG64
SyscallHookHandler(VOID);

[[nodiscard]] NTSTATUS Initialize(_In_ SSDT_CALLBACK SsdtCallback = Hooks::SsdtCallback);
#elif (SYSCALL_HOOK_TYPE == SYSCALL_HOOK_SSDT_HOOK)
[[nodiscard]] NTSTATUS Initialize();
#endif

void Unitialize();
void Cleanup();
}; // namespace SyscallHook