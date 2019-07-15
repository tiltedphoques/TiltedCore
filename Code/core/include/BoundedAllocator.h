#pragma once

#include "StandardAllocator.h"

class BoundedAllocator : public StandardAllocator
{
public:

    BoundedAllocator(size_t aMaximumAllocationSize);

    void* Allocate(size_t aSize) override;
    void Free(void* apData) override;

private:

    size_t m_availableMemory;
};