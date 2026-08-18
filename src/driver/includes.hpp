#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <type_traits>
#include <algorithm>

#include <ntifs.h>
#include <fltKernel.h>
#include <ntintsafe.h>
#include <minwindef.h>
#include <ntstrsafe.h>
#include <ntimage.h>
#include <bcrypt.h>
#include <intrin.h>
#include <evntrace.h>
#include <wmistr.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <phnt.h>
#include <ntfill.h>
#include <ntpebteb.h>
#include <ntldr.h>
#include <ntwow64.h>

#ifdef __cplusplus
}
#endif

#include <fnv1a/include/fnv1a.hpp>
#include <scope_guard/include/scope_guard.hpp>

#include "..\shared\shared.hpp"

#include "hde\hde64.h"
#include "trace.hpp"
#include "def.hpp"
#include "crc32.hpp"
#include "mutex.hpp"
#include "misc.hpp"
#include "memory.hpp"
#include "threads.hpp"
#include "dynamic.hpp"
#include "processes.hpp"
#include "hooks.hpp"
#include "syscall_hook.hpp"
#include "syscall_table.hpp"
#include "inject.hpp"
#include "bypass.hpp"
#include "ioctl.hpp"