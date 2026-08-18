#pragma once

#define DEFINE_DYN_CONTEXT_PROC(return_type, proc_name, var_type)                                                      \
    __forceinline return_type proc_name(var_type p)                                                                    \
    {                                                                                                                  \
        return reinterpret_cast<return_type>(PTR_OFFSET_ADD(p, Offset.proc_name));                                     \
    }

#define DEFINE_DYN_CONTEXT_PROC_PTR(return_type, proc_name, var_type)                                                  \
    __forceinline return_type proc_name(var_type p)                                                                    \
    {                                                                                                                  \
        return *reinterpret_cast<return_type *>(PTR_OFFSET_ADD(p, Offset.proc_name));                                  \
    }

namespace Dynamic
{
struct _DYNAMIC_CONTEXT
{
    struct
    {
        PVOID NtoskrnlBase;
        ULONG Major;
        ULONG Minor;
        ULONG Build;

        struct
        {
#if (SYSCALL_HOOK_TYPE == SYSCALL_HOOK_INFINITY_HOOK)
            ULONG_PTR EtwpDebuggerData;
            ULONG_PTR HvlpReferenceTscPage;
            ULONG_PTR HvlGetQpcBias;
#endif
            PULONG_PTR KeServiceDescriptorTable;

        } Address;

        struct
        {
#if (SYSCALL_HOOK_TYPE == SYSCALL_HOOK_INFINITY_HOOK)
            ULONG GetCpuClock;
#endif
        } Offset;

#if (SYSCALL_HOOK_TYPE == SYSCALL_HOOK_INFINITY_HOOK)
        DEFINE_DYN_CONTEXT_PROC(PVOID *, GetCpuClock, ULONG_PTR)
#endif
    } Kernel;

} inline g_DynamicContext{};

[[nodiscard]] NTSTATUS Initialize();
void Unitialize();

}; // namespace Dynamic

#define NTOS_BASE Dynamic::g_DynamicContext.Kernel.NtoskrnlBase
#define NTOS_MAJOR Dynamic::g_DynamicContext.Kernel.Major
#define NTOS_MINOR Dynamic::g_DynamicContext.Kernel.Minor
#define NTOS_BUILD Dynamic::g_DynamicContext.Kernel.Build