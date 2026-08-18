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

#include "includes.hpp"

namespace Mutex
{
NTSTATUS Resource::Initialize()
{
    PAGED_CODE();
    NT_ASSERT(!this->_initialized);

    if (this->_initialized)
    {
        return STATUS_ALREADY_INITIALIZED;
    }

    this->_resource = reinterpret_cast<PERESOURCE>(Memory::AllocNonPaged(sizeof(ERESOURCE), Memory::TAG_RESOURCE));
    if (!this->_resource)
    {
        WPP_PRINT(TRACE_LEVEL_ERROR, GENERAL, "Failed to allocate %u bytes for resource!", sizeof(ERESOURCE));
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    ExInitializeResourceLite(this->_resource);

    this->_initialized = true;

    return STATUS_SUCCESS;
}

void Resource::Destroy()
{
    PAGED_CODE();
    NT_ASSERT(this->_initialized);

    if (!this->_initialized)
    {
        return;
    }

    this->_initialized = false;

    // Wait until all references to the lock are released
    //
    while (InterlockedCompareExchange(&this->_refCount, 0, 0) != 0)
    {
        YieldProcessor();
    }

    ExDeleteResourceLite(this->_resource);
    Memory::FreePool(this->_resource);
}

void Resource::LockExclusive()
{
    PAGED_CODE();

    if (!this->_initialized)
    {
        return;
    }

    InterlockedIncrement(&this->_refCount);
    ExEnterCriticalRegionAndAcquireResourceExclusive(this->_resource);
}

void Resource::LockShared()
{
    PAGED_CODE();

    if (!this->_initialized)
    {
        return;
    }

    InterlockedIncrement(&this->_refCount);
    ExEnterCriticalRegionAndAcquireResourceShared(this->_resource);
}

void Resource::Unlock()
{
    PAGED_CODE();

    if (!this->_initialized)
    {
        return;
    }

    ExReleaseResourceAndLeaveCriticalRegion(this->_resource);
    InterlockedDecrement(&this->_refCount);
}

} // namespace Mutex