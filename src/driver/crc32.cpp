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