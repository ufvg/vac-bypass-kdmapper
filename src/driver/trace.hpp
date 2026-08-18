#pragma once

#include <evntrace.h>

#if DBG || FORCE_DBGPRINT
#define DBG_PRINT(s, ...) DbgPrintEx(0, 0, "[VAC] F: %s L: %d -- " s "\n", __FILE__, __LINE__, __VA_ARGS__)
#else
#define DBG_PRINT(s, ...)
#endif

#if !DBG
#define WPP_PRINT(a, b, s, ...) DBG_PRINT(s, __VA_ARGS__)
#define WPP_INIT_TRACING(...)
#define WPP_CLEANUP(...)

#define GENERAL

#else
#define WPP_GLOBALLOGGER
#define WPP_CHECK_FOR_NULL_STRING

// {BBB7063B-B267-4728-A95D-304A8E4E6A89}
#define WPP_CONTROL_GUIDS                                                                                              \
    WPP_DEFINE_CONTROL_GUID(VacCtrlGuid, (BBB7063B, B267, 4728, A95D, 304A8E4E6A89),                                   \
                            WPP_DEFINE_BIT(GENERAL) /* bit  0 = 0x00000001 */                                          \
    )

#define WPP_LEVEL_EVENT_LOGGER(level, event) WPP_LEVEL_LOGGER(event)
#define WPP_LEVEL_EVENT_ENABLED(level, event) (WPP_LEVEL_ENABLED(event) && WPP_CONTROL(WPP_BIT_##event).Level >= level)

#define TMH_STRINGIFYX(x) #x
#define TMH_STRINGIFY(x) TMH_STRINGIFYX(x)

#ifdef TMH_FILE
#include TMH_STRINGIFY(TMH_FILE)
#endif
#endif