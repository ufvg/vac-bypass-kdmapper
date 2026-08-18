/******************************************************************************
 * Copyright (c) [2024] [Ricardo Carvalho (@crvvdev)]
 * All rights reserved.
 *
 * This software is the confidential and proprietary information of
 * Ricardo Carvalho (@crvvdev). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Ricardo Carvalho.
 ******************************************************************************/
#pragma once

namespace Processes
{
typedef struct _PROCESS_ENTRY
{
    LIST_ENTRY ListEntry;
    PEPROCESS Process;
    HANDLE ProcessId;
    union {
        struct
        {
            BOOLEAN Steam : 1;
            BOOLEAN SteamService : 1;
            BOOLEAN Game : 1;
        } Flags;
        ULONG Long;
    };

} PROCESS_ENTRY, *PPROCESS_ENTRY;

inline NPAGED_LOOKASIDE_LIST g_ProcessesLookasideList{};
inline LIST_ENTRY g_ProcessesList{};
inline Mutex::Resource g_ProcessesListLock;

[[nodiscard]] NTSTATUS Initialize();
void Unitialize();

[[nodiscard]] PEPROCESS GetGameProcess(void);

[[nodiscard]] BOOLEAN IsProcessSteam(_In_ HANDLE ProcessId);
[[nodiscard]] BOOLEAN IsProcessGame(_In_ HANDLE ProcessId);
[[nodiscard]] BOOLEAN IsProcessInList(_In_ HANDLE ProcessId);

[[nodiscard]] BOOLEAN IsProcessSteamUnsafe(_In_ HANDLE ProcessId);
[[nodiscard]] BOOLEAN IsProcessGameUnsafe(_In_ HANDLE ProcessId);
[[nodiscard]] BOOLEAN IsProcessInListUnsafe(_In_ HANDLE ProcessId);

[[nodiscard]] BOOLEAN IsSteamOrSteamServiceInList(void);

[[nodiscard]] NTSTATUS AddProcessGame(_In_ HANDLE ProcessId);
[[nodiscard]] NTSTATUS AddProcessSteam(_In_ HANDLE ProcessId);
[[nodiscard]] NTSTATUS AddProcessSteamService(_In_ HANDLE ProcessId);

[[nodiscard]] BOOLEAN RemoveProcess(_In_ HANDLE ProcessId);

using ENUM_PROCESSES = BOOLEAN (*)(_In_ PPROCESS_ENTRY);

template <typename C = ENUM_PROCESSES> __forceinline BOOLEAN EnumProcessesUnsafe(const C &Callback)
{
    NT_ASSERT(CURRENT_IRQL <= DISPATCH_LEVEL);

    LIST_ENTRY *pListHead = &g_ProcessesList;

    if (IsListEmpty(pListHead))
    {
        return FALSE;
    }

    PPROCESS_ENTRY pEntry = NULL;
    LIST_ENTRY *pListEntry = pListHead->Flink;
    BOOLEAN result = FALSE;

    while (pListEntry != pListHead)
    {
        pEntry = CONTAINING_RECORD(pListEntry, PROCESS_ENTRY, ListEntry);
        pListEntry = pListEntry->Flink;

        if (Callback(pEntry))
        {
            result = TRUE;
            break;
        }
    }
    return result;
}

} // namespace Processes