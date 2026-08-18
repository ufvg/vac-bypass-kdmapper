#pragma once

namespace Comms
{
[[nodiscard]] NTSTATUS HandleIoctl(_In_ PVOID data, _In_ ULONG dataSize);
}; // namespace Comms