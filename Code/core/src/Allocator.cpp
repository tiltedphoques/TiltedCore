#include "Allocator.h"
#include "StandardAllocator.h"
#include <cassert>


thread_local Allocator* Allocator::s_allocatorStack[kMaxAllocatorCount];
thread_local int Allocator::s_currentAllocator{ -1 };


void Allocator::Push(Allocator* apAllocator)
{
    assert(s_currentAllocator + 1 < kMaxAllocatorCount);

    s_currentAllocator++;
    s_allocatorStack[s_currentAllocator] = apAllocator;
}

void Allocator::Push(Allocator& aAllocator)
{
    Push(&aAllocator);
}

Allocator* Allocator::Pop()
{
    assert(s_currentAllocator >= 0);

    const auto pAllocator = s_allocatorStack[s_currentAllocator];
    s_currentAllocator--;

    return pAllocator;
}

Allocator* Allocator::Get()
{
    if (s_currentAllocator >= 0)
    {
        return s_allocatorStack[s_currentAllocator];
    }

    return GetDefault();
}

Allocator* Allocator::GetDefault()
{
    static StandardAllocator s_allocator;
    return &s_allocator;
}

ScopedAllocator::ScopedAllocator(Allocator* apAllocator)
    : m_pAllocator(apAllocator)
{
    Allocator::Push(m_pAllocator);
}

ScopedAllocator::ScopedAllocator(Allocator& aAllocator)
    : ScopedAllocator(&aAllocator)
{
}

ScopedAllocator::~ScopedAllocator()
{
    Allocator::Pop();
}
