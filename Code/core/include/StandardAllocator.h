#pragma once

#include "Allocator.h"

class StandardAllocator : public Allocator
{
public:

    void* Allocate(size_t aSize) override;
    void Free(void* apData) override;
    size_t Size(void* apData) override;
};