#include "includes.hpp"

namespace Comms
{

typedef struct _INJECT_IMAGE_CONTEXT
{
    PEPROCESS Process;
    PVOID ImageBase;
    ULONG ImageSize;
    NTSTATUS Status;
    KEVENT Event;
    WORK_QUEUE_ITEM WorkItem;
} INJECT_IMAGE_CONTEXT, *PINJECT_IMAGE_CONTEXT;

static void InjectImageWorkerRoutine(_In_ PVOID param)
{
    PAGED_CODE();
    NT_ASSERT(param);

    auto context = reinterpret_cast<PINJECT_IMAGE_CONTEXT>(param);

    // Attach to process context and inject image
    //
    context->Status = Inject::AttachAndInject(context->Process, context->ImageBase, context->ImageSize);

    KeSetEvent(&context->Event, IO_NO_INCREMENT, FALSE);
}

NTSTATUS HandleIoctl(_In_ PVOID data, _In_ ULONG dataSize)
{
    PAGED_CODE();
    NT_ASSERT(data);

    // Communication request handlers
    //
    auto HandleDisableBypass = [](PDRIVER_REQUEST_DISABLE_BYPASS request) -> NTSTATUS {
        NTSTATUS status;
        __try
        {
            Hooks::g_shouldBypass = false;

            WPP_PRINT(TRACE_LEVEL_VERBOSE, GENERAL, "Bypass is currently disabled!");

            request->SetStatus(STATUS_SUCCESS);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            status = GetExceptionCode();
            return status;
        }
        return STATUS_SUCCESS;
    };

    auto HandleEnableBypass = [](PDRIVER_REQUEST_ENABLE_BYPASS request) -> NTSTATUS {
        NTSTATUS status;
        __try
        {
            Hooks::g_shouldBypass = true;

            WPP_PRINT(TRACE_LEVEL_VERBOSE, GENERAL, "Bypass is currently enabled!");

            request->SetStatus(STATUS_SUCCESS);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            status = GetExceptionCode();
            return status;
        }
        return STATUS_SUCCESS;
    };

    auto HandleRegisterProcess = [](PDRIVER_REQUEST_REGISTER_PROCESS request) -> NTSTATUS {
        NTSTATUS status = STATUS_UNSUCCESSFUL;

        __try
        {
            if (request->Add)
            {
                switch (request->Role)
                {
                case 1: // Steam
                    status = Processes::AddProcessSteam(request->ProcessId);
                    break;
                case 2: // SteamService
                    status = Processes::AddProcessSteamService(request->ProcessId);
                    break;
                case 3: // Game
                    status = Processes::AddProcessGame(request->ProcessId);
                    break;
                default:
                    status = STATUS_INVALID_PARAMETER;
                    break;
                }

                // If the process is already registered, treat it as success
                if (status == STATUS_ALREADY_REGISTERED)
                {
                    status = STATUS_SUCCESS;
                }
            }
            else
            {
                if (Processes::IsProcessInList(request->ProcessId))
                {
                    Bypass::EraseGameModules(request->ProcessId);
                    Bypass::EraseProtectedModules(request->ProcessId);
                    (void)Processes::RemoveProcess(request->ProcessId);
                }
                status = STATUS_SUCCESS;
            }

            request->SetStatus(status);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            status = GetExceptionCode();
        }

        return status;
    };

    auto HandleInject = [](PDRIVER_REQUEST_INJECT request) -> NTSTATUS {
        NTSTATUS status = STATUS_UNSUCCESSFUL;
        PVOID imageBase = nullptr;
        PEPROCESS process = nullptr;
        PINJECT_IMAGE_CONTEXT imageContext = nullptr;

        if (request->ImageSize <= 0)
        {
            status = STATUS_INVALID_PARAMETER;
            goto Exit;
        }

        __try
        {
            Hooks::g_shouldBypass = true;

            ProbeForRead(request->ImageBase, request->ImageSize, alignof(PVOID));

            // Store image in kernel memory
            //
            imageBase = Memory::AllocNonPaged(request->ImageSize, Memory::TAG_DEFAULT);
            if (!imageBase)
            {
                WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "Failed to allocate %u bytes for image!", request->ImageSize);
                status = STATUS_INSUFFICIENT_RESOURCES;
                goto Exit;
            }

            RtlCopyMemory(imageBase, request->ImageBase, request->ImageSize);

            process = Processes::GetGameProcess();
            if (!process)
            {
                WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "Failed to get game process!");
                status = STATUS_UNSUCCESSFUL;
                goto Exit;
            }

            // Build inject image context
            //
            imageContext = reinterpret_cast<PINJECT_IMAGE_CONTEXT>(
                Memory::AllocNonPaged(sizeof(INJECT_IMAGE_CONTEXT), Memory::TAG_DEFAULT));
            if (!imageContext)
            {
                WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "Failed to allocate %u bytes for image context!",
                          sizeof(INJECT_IMAGE_CONTEXT));
                status = STATUS_INSUFFICIENT_RESOURCES;
                goto Exit;
            }

            // We will be issuing a worker item to do the job.
            //
            imageContext->Process = process;
            imageContext->ImageBase = imageBase;
            imageContext->ImageSize = request->ImageSize;
            imageContext->Status = STATUS_UNSUCCESSFUL;
            KeInitializeEvent(&imageContext->Event, NotificationEvent, FALSE);
            ExInitializeWorkItem(&imageContext->WorkItem, &InjectImageWorkerRoutine, imageContext);
            ExQueueWorkItem(&imageContext->WorkItem, DelayedWorkQueue);

            // Wait for worker item to finish
            //
            status = KeWaitForSingleObject(&imageContext->Event, Executive, KernelMode, FALSE, nullptr);
            if (!NT_SUCCESS(status))
            {
                WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "KeWaitForSingleObject returned %!STATUS!", status);
                goto Exit;
            }

            status = imageContext->Status;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            status = GetExceptionCode();
        }

    Exit:
        if (imageContext)
        {
            Memory::FreePool(imageContext);
        }

        if (process)
        {
            ObDereferenceObject(process);
        }

        request->SetStatus(status);
        return status;
    };

    // Check if request is valid and process it
    //
    NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;

    if (dataSize < sizeof(DRIVER_REQUEST_HEADER))
    {
        return status;
    }

    const auto requestData = static_cast<PDRIVER_REQUEST_HEADER>(data);
    if (!requestData->IsValid())
    {
        WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "Invalid communication request data!");
        return status;
    }

    switch (requestData->Request)
    {
    case EDriverCommunicationRequest::DisableBypass: {
        if (dataSize < sizeof(DRIVER_REQUEST_DISABLE_BYPASS))
        {
            status = STATUS_INVALID_PARAMETER_1;
            break;
        }
        return HandleDisableBypass(reinterpret_cast<PDRIVER_REQUEST_DISABLE_BYPASS>(data));
    }
    case EDriverCommunicationRequest::EnableBypass: {
        if (dataSize < sizeof(DRIVER_REQUEST_ENABLE_BYPASS))
        {
            status = STATUS_INVALID_PARAMETER_1;
            break;
        }
        return HandleEnableBypass(reinterpret_cast<PDRIVER_REQUEST_ENABLE_BYPASS>(data));
    }
    case EDriverCommunicationRequest::RegisterProcess: {
        if (dataSize < sizeof(DRIVER_REQUEST_REGISTER_PROCESS))
        {
            status = STATUS_INVALID_PARAMETER_1;
            break;
        }
        return HandleRegisterProcess(reinterpret_cast<PDRIVER_REQUEST_REGISTER_PROCESS>(data));
    }
    case EDriverCommunicationRequest::InjectDll: {
        if (dataSize < sizeof(DRIVER_REQUEST_INJECT))
        {
            status = STATUS_INVALID_PARAMETER_1;
            break;
        }
        return HandleInject(reinterpret_cast<PDRIVER_REQUEST_INJECT>(data));
    }
    }

    return status;
}

} // namespace Comms