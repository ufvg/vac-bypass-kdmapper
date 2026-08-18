/******************************************************************************
 * Copyright (c) [2024] [Ricardo Carvalho (@crvvdev)]
 * All rights reserved.
 *
 * This software is the confidential and proprietary information of
 * Ricardo Carvalho (@crvvdev). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Ricardo Carvalho.
 ******************************************************************************/
#include "includes.hpp"

namespace Threads
{
bool g_initialized = false;

const bool IsInitialized()
{
    return g_initialized;
}

NTSTATUS Initialize()
{
    PAGED_PASSIVE();

    if (g_initialized)
    {
        return STATUS_ALREADY_INITIALIZED;
    }

    const NTSTATUS Status = g_ThreadsListLock.Initialize();
    if (!NT_SUCCESS(Status))
    {
        WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "Failed to initialized threads list lock!");
        return STATUS_UNSUCCESSFUL;
    }

    InitializeListHead(&g_ThreadsList);

    g_initialized = true;

    return STATUS_SUCCESS;
}

void Unitialize()
{
    PAGED_PASSIVE();

    if (!g_initialized)
    {
        return;
    }

    NTSTATUS Status;

    constexpr ULONG waitMaxNum = MAXIMUM_WAIT_OBJECTS;

    auto Objects = reinterpret_cast<PVOID *>(Memory::AllocNonPaged(sizeof(PVOID) * waitMaxNum, Memory::TAG_DEFAULT));
    if (!Objects)
    {
        WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "Failed to allocate memory for awaiting objects!");
        return;
    }

    SCOPE_EXIT
    {
        Memory::FreePool(Objects);
    };

    auto Handles = reinterpret_cast<PHANDLE>(Memory::AllocNonPaged(sizeof(PVOID) * waitMaxNum, Memory::TAG_DEFAULT));
    if (!Handles)
    {
        WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "Failed to allocate memory for awaiting handles!");
        return;
    }

    SCOPE_EXIT
    {
        Memory::FreePool(Handles);
    };

    int i = 0;

    //
    // Check to see if there are any thread that was not stopped, if so signalize
    // it to stop and add to waiting list.
    //
    g_ThreadsListLock.LockExclusive();

    EnumThreadsUnsafe([&](PKERNEL_THREAD Entry) [[msvc::forceinline]] -> BOOLEAN {
        if (Entry->Status == KERNEL_THREAD_STATUS::Stopped)
        {
            goto Exit;
        }

        // Signalize thread to stop
        //
        StopThread(Entry, FALSE);

        // Add to awaiting objects list
        //
        if (i < waitMaxNum)
        {
            Objects[i] = Entry->Object;
            Handles[i] = Entry->Handle;
            i++;
        }

    Exit:
        // Remove from list
        //
        RemoveEntryList(&Entry->ListEntry);

        return FALSE;
    });

    g_ThreadsListLock.Unlock();
    g_ThreadsListLock.Destroy();

    if (i > 0)
    {
        WPP_PRINT(TRACE_LEVEL_VERBOSE, GENERAL, "Waiting for %d threads to stop...", i);

        auto waitBlockArray =
            reinterpret_cast<PKWAIT_BLOCK>(Memory::AllocNonPaged(sizeof(KWAIT_BLOCK) * i, Memory::TAG_DEFAULT));
        if (!waitBlockArray)
        {
            WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "Failed to allocate memory for wait block array!");
            return;
        }

        SCOPE_EXIT
        {
            Memory::FreePool(waitBlockArray);
        };

        // Wait for all threads to stop.
        Status = KeWaitForMultipleObjects(i, Objects, WaitAll, Executive, KernelMode, FALSE, nullptr, waitBlockArray);

        NT_ASSERT(NT_SUCCESS(Status));

        while (i--)
        {
            ObDereferenceObject(Objects[i]);
            ZwClose(Handles[i]);
        }

        WPP_PRINT(TRACE_LEVEL_VERBOSE, GENERAL, "All threads have been stopped successfully!");
    }
    else
    {
        WPP_PRINT(TRACE_LEVEL_VERBOSE, GENERAL, "No threads needed to stop.");
    }

    g_initialized = false;

    WPP_PRINT(TRACE_LEVEL_INFORMATION, GENERAL, "Unitialized Threads");
}

void ThreadStub(PVOID Params)
{
    PAGED_PASSIVE();

    auto ThreadParams = reinterpret_cast<Threads::PKERNEL_THREAD>(Params);
    if (!ThreadParams)
    {
        goto Exit;
    }

    while (ThreadParams->Stop == FALSE)
    {
        if (ThreadParams->Callback(ThreadParams->StartContext))
        {
            break;
        }
        YieldProcessor();
    }

    ThreadParams->Status = KERNEL_THREAD_STATUS::Stopped;

Exit:
    WPP_PRINT(TRACE_LEVEL_VERBOSE, GENERAL, "Thread %d is terminating...", HandleToULong(PsGetCurrentThreadId()));
    PsTerminateSystemThread(STATUS_SUCCESS);
}

BOOLEAN CreateThread(KERNEL_THREAD_CALLBACK Callback, PVOID StartContext, PKERNEL_THREAD Thread)
{
    PAGED_CODE();
    NT_ASSERT(Thread);

    if (!IsInitialized())
    {
        return FALSE;
    }

    NTSTATUS Status;
    HANDLE threadHandle = NULL;
    CLIENT_ID ClientId = {};

    Thread->Stop = FALSE;
    Thread->Callback = Callback;
    Thread->StartContext = StartContext;

    Status = PsCreateSystemThread(&threadHandle, GENERIC_ALL, nullptr, NULL, &ClientId, &ThreadStub, Thread);
    if (!NT_SUCCESS(Status))
    {
        WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "PsCreateSystemThread returned %!STATUS!", Status);
        return FALSE;
    }

    Status = ObReferenceObjectByHandle(threadHandle, 0, *PsThreadType, KernelMode,
                                       reinterpret_cast<PVOID *>(&Thread->Object), nullptr);
    if (!NT_SUCCESS(Status))
    {
        StopThread(Thread, TRUE);

        WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "ObReferenceObjectByHandle returned %!STATUS!", Status);
        return FALSE;
    }

    Thread->ClientId = ClientId;
    Thread->Handle = threadHandle;
    Thread->Status = KERNEL_THREAD_STATUS::Running;

    g_ThreadsListLock.LockExclusive();
    InsertTailList(&g_ThreadsList, &Thread->ListEntry);
    g_ThreadsListLock.Unlock();

    return TRUE;
}

void StopThread(PKERNEL_THREAD Thread, BOOLEAN Wait)
{
    PAGED_CODE();
    NT_ASSERT(Thread);

    Thread->Stop = TRUE;

    if (Wait)
    {
        if (Thread->Object)
        {
            [[maybe_unused]] NTSTATUS Status =
                KeWaitForSingleObject(Thread->Object, Executive, KernelMode, FALSE, nullptr);
            NT_ASSERT(NT_SUCCESS(Status));

            ObDereferenceObject(Thread->Object);
            Thread->Object = nullptr;
        }

        if (Thread->Handle)
        {
            ZwClose(Thread->Handle);
            Thread->Handle = nullptr;
        }
    }
}
} // namespace Threads