#pragma once

namespace Threads
{
using KERNEL_THREAD_CALLBACK = BOOLEAN (*)(PVOID);

enum class KERNEL_THREAD_STATUS : UINT8
{
    Running,
    Stopped
};

typedef struct _KERNEL_THREAD
{
    LIST_ENTRY ListEntry;
    CLIENT_ID ClientId;
    HANDLE Handle;
    PVOID Object;
    PVOID StartContext;
    BOOLEAN Stop;
    KERNEL_THREAD_STATUS Status;
    KERNEL_THREAD_CALLBACK Callback;

} KERNEL_THREAD, *PKERNEL_THREAD;

inline LIST_ENTRY g_ThreadsList{};
inline Mutex::Resource g_ThreadsListLock;

using ENUM_THREAD_CALLBACK = BOOLEAN (*)(PKERNEL_THREAD pEntry);

/// <summary>
///
/// </summary>
/// <returns></returns>
NTSTATUS Initialize();

/// <summary>
///
/// </summary>
void Unitialize();

/// <summary>
///
/// </summary>
/// <param name="Callback"></param>
/// <param name="StartContext"></param>
/// <param name="Thread"></param>
/// <returns></returns>
BOOLEAN CreateThread(KERNEL_THREAD_CALLBACK Callback, PVOID StartContext, PKERNEL_THREAD Thread);

/// <summary>
///
/// </summary>
/// <param name="Thread"></param>
/// <param name="Wait"></param>
void StopThread(PKERNEL_THREAD Thread, BOOLEAN Wait = FALSE);

/// <summary>
///
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="Callback"></param>
/// <returns></returns>
template <typename T = ENUM_THREAD_CALLBACK> BOOLEAN EnumThreadsUnsafe(const T &&Callback)
{
    NT_ASSERT(CURRENT_IRQL <= DISPATCH_LEVEL);

    LIST_ENTRY *pListHead = &g_ThreadsList;

    if (IsListEmpty(pListHead))
    {
        return FALSE;
    }

    PKERNEL_THREAD pEntry = nullptr;
    LIST_ENTRY *pListEntry = pListHead->Flink;
    BOOLEAN result = FALSE;

    while (pListEntry != pListHead)
    {
        pEntry = CONTAINING_RECORD(pListEntry, KERNEL_THREAD, ListEntry);
        pListEntry = pListEntry->Flink;

        if (Callback(pEntry))
        {
            result = TRUE;
            break;
        }
    }

    return result;
}

} // namespace Threads