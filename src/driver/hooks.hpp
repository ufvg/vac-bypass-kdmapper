#pragma once

#define SYSCALL_HOOK_INFINITY_HOOK 0
#define SYSCALL_HOOK_SSDT_HOOK 1

#ifndef SYSCALL_HOOK_TYPE
#define SYSCALL_HOOK_TYPE SYSCALL_HOOK_SSDT_HOOK
#endif

namespace Hooks
{
extern volatile LONG g_hooksRefCount;
extern bool g_shouldBypass;

typedef struct _SYSCALL_HOOK_ENTRY
{
    FNV1A_t ServiceNameHash;
    ULONG ServiceIndex;
    PVOID OriginalRoutineAddress;
    PVOID NewRoutineAddress;
#if (SYSCALL_HOOK_TYPE == SYSCALL_HOOK_SSDT_HOOK)
    LONG OldSsdt;
    LONG NewSsdt;
    UCHAR OriginalBytes[12];
#endif
} SYSCALL_HOOK_ENTRY, *PSYSCALL_HOOK_ENTRY;

extern NTSTATUS NTAPI hkNtQuerySystemInformation(IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
                                                 OUT PVOID SystemInformation, IN ULONG SystemInformationLength,
                                                 OUT PULONG ReturnLength OPTIONAL);

extern NTSTATUS NTAPI hkNtReadVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer,
                                            SIZE_T NumberOfBytesToRead, PSIZE_T NumberOfBytesReaded);

extern NTSTATUS NTAPI hkNtQueryVirtualMemory(_In_ HANDLE ProcessHandle, _In_opt_ PVOID BaseAddress,
                                             _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
                                             _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
                                             _In_ SIZE_T MemoryInformationLength, _Out_opt_ PSIZE_T ReturnLength);

extern NTSTATUS NTAPI hkNtMapViewOfSection(_In_ HANDLE SectionHandle, _In_ HANDLE ProcessHandle,
                                           _Outptr_result_bytebuffer_(*ViewSize) PVOID *BaseAddress,
                                           _In_ ULONG_PTR ZeroBits, _In_ SIZE_T CommitSize,
                                           _Inout_opt_ PLARGE_INTEGER SectionOffset, _Inout_ PSIZE_T ViewSize,
                                           _In_ SECTION_INHERIT InheritDisposition, _In_ ULONG AllocationType,
                                           _In_ ULONG Win32Protect);

inline SYSCALL_HOOK_ENTRY g_SyscallHookList[] = {
    {FNV("NtMapViewOfSection"), ULONG_MAX, nullptr, &hkNtMapViewOfSection},
    {FNV("NtReadVirtualMemory"), ULONG_MAX, nullptr, &hkNtReadVirtualMemory},
    {FNV("NtQueryVirtualMemory"), ULONG_MAX, nullptr, &hkNtQueryVirtualMemory},
    {FNV("NtQuerySystemInformation"), ULONG_MAX, nullptr, &hkNtQuerySystemInformation},
};

void __fastcall SsdtCallback(ULONG ssdt_index, VOID **ssdt_address);

[[nodiscard]] NTSTATUS Initialize();
void Unitialize();

} // namespace Hooks