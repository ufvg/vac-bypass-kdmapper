#pragma once

namespace SyscallTable
{
typedef struct _SYSTEM_SERVICE_INFO
{
    FNV1A_t ServiceHash;
    ULONG ServiceIndex;
    ULONG_PTR RoutineAddress;

} SYSTEM_SERVICE_INFO, *PSYSTEM_SERVICE_INFO;

inline RTL_AVL_TABLE g_SyscallAvlTable = {};

[[nodiscard]] NTSTATUS Initialize();
void Unitialize();

BOOLEAN FindServiceInTable(_In_ const FNV1A_t ServiceHash, _Out_opt_ PULONG ServiceIndex,
                           _Out_ PULONG_PTR RoutineAddress);

} // namespace SyscallTable