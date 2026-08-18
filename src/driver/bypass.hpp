/******************************************************************************
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

namespace Bypass
{
static const wchar_t *g_BackupModulesList[] = {
    L"\\bin\\win64\\client.dll",      L"\\bin\\win64\\engine.dll",           L"\\bin\\win64\\materialsystem2.dll",
    L"\\bin\\win64\\inputsystem.dll", L"\\bin\\win64\\rendersystemdx11.dll", L"\\bin\\win64\\rendersystemvulkan.dll",
    L"\\bin\\win64\\inputsystem.dll", L"\\bin\\win64\\scenesystem.dll"};

typedef struct _GAME_MODULE_ENTRY
{
    LIST_ENTRY ListEntry;
    HANDLE ProcessId;
    ULONG_PTR BaseAddress;
    ULONG SizeOfImage;
    ULONG BaseOfCode;
    ULONG SizeOfCode;
    ULONG_PTR CopyBaseAddress;
    SIZE_T CopyAllocatedSize;

} GAME_MODULE_ENTRY, *PGAME_MODULE_ENTRY;

inline NPAGED_LOOKASIDE_LIST g_GameModulesLookasideList{};
inline LIST_ENTRY g_GameModulesList{};
inline Mutex::Resource g_GameModulesListLock;

typedef struct _PROTECTED_MODULE_ENTRY
{
    LIST_ENTRY ListEntry;
    HANDLE ProcessId;
    ULONG_PTR AllocatedBase;
    SIZE_T RegionSize;

} PROTECTED_MODULE_ENTRY, *PPROTECTED_MODULE_ENTRY;

inline NPAGED_LOOKASIDE_LIST g_ProtectedModulesLookasideList{};
inline LIST_ENTRY g_ProtectedModulesList{};
inline Mutex::Resource g_ProtectedModulesListLock;

[[nodiscard]] NTSTATUS Initialize();
void Unitialize();

[[nodiscard]] NTSTATUS CreateGameModule(_In_ HANDLE ProcessId, _In_ PVOID MappedBase, _In_ SIZE_T MappedSize,
                                        _In_ PUNICODE_STRING MappedName);
[[nodiscard]] NTSTATUS CreateProtectedModule(_In_ HANDLE ProcessId, _In_ PVOID MappedBase, _In_ SIZE_T MappedSize);

[[nodiscard]] BOOLEAN IsInGameModuleMemoryRangeUnsafe(_In_ HANDLE ProcessId, _Out_opt_ PVOID *Object,
                                                      _In_ PVOID BaseAddress, _In_opt_ SIZE_T Range = 0ULL);
[[nodiscard]] BOOLEAN IsInProtectedModuleMemoryRangeUnsafe(_In_ HANDLE ProcessId, _Out_opt_ PVOID *Object,
                                                           _In_ PVOID BaseAddress, _In_opt_ SIZE_T Range = 0ULL);

[[nodiscard]] BOOLEAN IsInGameModuleMemoryRange(_In_ HANDLE ProcessId, _Out_opt_ PVOID *Object, _In_ PVOID BaseAddress,
                                                _In_opt_ SIZE_T Range = 0ULL);
[[nodiscard]] BOOLEAN IsInProtectedModuleMemoryRange(_In_ HANDLE ProcessId, _Out_opt_ PVOID *Object,
                                                     _In_ PVOID BaseAddress, _In_opt_ SIZE_T Range = 0ULL);

void EraseGameModules(_In_ HANDLE ProcessId);
void EraseProtectedModules(_In_ HANDLE ProcessId);

using ENUM_GAME_MODULES = BOOLEAN (*)(_In_ PGAME_MODULE_ENTRY);
using ENUM_PROTECTED_MODULES = BOOLEAN (*)(_In_ PPROTECTED_MODULE_ENTRY);

template <typename C = ENUM_GAME_MODULES> __forceinline BOOLEAN EnumGameModulesUnsafe(_In_ const C &Callback)
{
    NT_ASSERT(CURRENT_IRQL <= DISPATCH_LEVEL);

    LIST_ENTRY *listHead = &g_GameModulesList;

    if (IsListEmpty(listHead))
    {
        return FALSE;
    }

    PGAME_MODULE_ENTRY entry = nullptr;
    LIST_ENTRY *listEntry = listHead->Flink;
    BOOLEAN result = FALSE;

    while (listEntry != listHead)
    {
        entry = CONTAINING_RECORD(listEntry, GAME_MODULE_ENTRY, ListEntry);
        listEntry = listEntry->Flink;

        if (Callback(entry))
        {
            result = TRUE;
            break;
        }
    }
    return result;
}

template <typename C = ENUM_PROTECTED_MODULES> __forceinline BOOLEAN EnumProtectedModulesUnsafe(_In_ const C &Callback)
{
    NT_ASSERT(CURRENT_IRQL <= DISPATCH_LEVEL);

    LIST_ENTRY *listHead = &g_ProtectedModulesList;

    if (IsListEmpty(listHead))
    {
        return FALSE;
    }

    PPROTECTED_MODULE_ENTRY entry = nullptr;
    LIST_ENTRY *listEntry = listHead->Flink;
    BOOLEAN result = FALSE;

    while (listEntry != listHead)
    {
        entry = CONTAINING_RECORD(listEntry, PROTECTED_MODULE_ENTRY, ListEntry);
        listEntry = listEntry->Flink;

        if (Callback(entry))
        {
            result = TRUE;
            break;
        }
    }
    return result;
}
} // namespace Bypass