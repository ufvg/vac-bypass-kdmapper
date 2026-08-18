#include "includes.hpp"

namespace Crc32
{
ULONG Checksum(_In_ const void *data, _In_ ULONG length)
{
    ULONG crc = 0xFFFFFFFF;
    const PUCHAR buf = (const PUCHAR)data;

    for (auto i = 0ul; i < length; i++)
    {
        crc = g_Crc32Table[(crc ^ buf[i]) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ 0xFFFFFFFF;
}
} // namespace Crc32