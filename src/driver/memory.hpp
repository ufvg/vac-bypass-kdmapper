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

namespace Memory
{
static constexpr ULONG TAG_DEFAULT = '0CAV';
static constexpr ULONG TAG_FILE = '1CAV';
static constexpr ULONG TAG_IMAGE = '2CAV';
static constexpr ULONG TAG_PROCESS = '3CAV';
static constexpr ULONG TAG_GAME_MODULE = '4CAV';
static constexpr ULONG TAG_PROTECTED_MODULE = '5CAV';
static constexpr ULONG TAG_SYSCALL_TABLE = '6CAV';
static constexpr ULONG TAG_SYSCALL_HOOK = '7CAV';
static constexpr ULONG TAG_CLASS = '8CAV';
static constexpr ULONG TAG_RESOURCE = '9CAV';

/// <summary>
/// Allocates non paged pool zero
/// </summary>
/// <param name="Size">Number of bytes to allocate</param>
/// <param name="Tag">Tag</param>
/// <returns>Pool pointer</returns>
__forceinline PVOID AllocNonPaged(_In_ SIZE_T Size, _In_ ULONG Tag)
{
    PVOID Pool = ExAllocatePoolWithTag(NonPagedPool, Size, Tag);
    if (Pool)
    {
        RtlZeroMemory(Pool, Size);
    }
    return Pool;
}

/// <summary>
/// Free allocated pool
/// </summary>
/// <param name="Pool">Pool to be free</param>
__forceinline void FreePool(_In_ PVOID P)
{
    NT_ASSERT(P);

    if (P)
    {
        ExFreePool(P);
    }
}

/// <summary>
/// Initializes non paged lookaside list
/// </summary>
/// <param name="LookasideList">Lookaside list</param>
/// <param name="Size">Size</param>
/// <param name="Tag">Tag</param>
_IRQL_requires_max_(DISPATCH_LEVEL) __forceinline void InitializeNPagedLookaside(
    _Out_ NPAGED_LOOKASIDE_LIST *LookasideList, _In_ SIZE_T Size, _In_ ULONG Tag)
{
    PAGED_PASSIVE();
    NT_ASSERT(LookasideList);

    ExInitializeNPagedLookasideList(LookasideList, nullptr, nullptr, NULL, Size, Tag, NULL);
}

/// <summary>
/// Delete lookaside list
/// </summary>
/// <param name="LookasideList">Lookaside list</param>
_IRQL_requires_max_(DISPATCH_LEVEL) __forceinline void DeleteNPagedLookaside(
    _Inout_ NPAGED_LOOKASIDE_LIST *LookasideList)
{
    PAGED_PASSIVE();
    NT_ASSERT(LookasideList);

    ExDeleteNPagedLookasideList(LookasideList);
}

/// <summary>
/// Allocate from non paged lookaside list
/// </summary>
/// <param name="LookasideList">Lookaside list</param>
/// <returns>Allocated pool</returns>
_IRQL_requires_max_(DISPATCH_LEVEL) __forceinline PVOID
    AllocFromNPagedLookaside(_Inout_ NPAGED_LOOKASIDE_LIST *LookasideList)
{
    PAGED_PASSIVE();
    NT_ASSERT(LookasideList);

    PVOID Pool = ExAllocateFromNPagedLookasideList(LookasideList);
    if (Pool)
    {
        RtlZeroMemory(Pool, LookasideList->L.Size);
    }
    return Pool;
}

/// <summary>
/// Free from lookaside list
/// </summary>
/// <param name="LookasideList">Lookaside list</param>
/// <param name="Pool">Pool pointer</param>
_IRQL_requires_max_(DISPATCH_LEVEL) __forceinline void FreeFromNPagedLookaside(
    _Inout_ NPAGED_LOOKASIDE_LIST *LookasideList, PVOID Pool)
{
    PAGED_PASSIVE();
    NT_ASSERT(LookasideList);
    NT_ASSERT(Pool);

    ExFreeToNPagedLookasideList(LookasideList, Pool);
}
} // namespace Memory