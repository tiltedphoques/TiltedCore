#pragma once

#include "Allocator.h"

class ScratchAllocator : public Allocator
{
public:

    ScratchAllocator(size_t aSize);
    virtual ~ScratchAllocator();

    void* Allocate(size_t aSize) override;
    void Free(void* apData) override;
    size_t Size(void* apData) override;
    void Reset();

private:

    size_t m_size;
    size_t m_baseSize;
    void* m_pData;
    void* m_pBaseData;
};