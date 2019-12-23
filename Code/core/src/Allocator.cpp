#include "Allocator.hpp"
#include "MimallocAllocator.hpp"
#include <cassert>

namespace TiltedPhoques
{
    thread_local Allocator* Allocator::s_allocatorStack[kMaxAllocatorCount];
    thread_local int Allocator::s_currentAllocator{ -1 };

    void Allocator::Push(Allocator* apAllocator) noexcept
    {
        assert(s_currentAllocator + 1 < kMaxAllocatorCount);

        s_currentAllocator++;
        s_allocatorStack[s_currentAllocator] = apAllocator;
    }

    void Allocator::Push(Allocator& aAllocator) noexcept
    {
        Push(&aAllocator);
    }

    Allocator* Allocator::Pop() noexcept
    {
        assert(s_currentAllocator >= 0);

        const auto pAllocator = s_allocatorStack[s_currentAllocator];
        s_currentAllocator--;

        return pAllocator;
    }

    Allocator* Allocator::Get() noexcept
    {
        if (s_currentAllocator >= 0)
        {
            return s_allocatorStack[s_currentAllocator];
        }

        return GetDefault();
    }

    Allocator* Allocator::GetDefault() noexcept
    {
        static MimallocAllocator s_allocator;
        return &s_allocator;
    }

    ScopedAllocator::ScopedAllocator(Allocator* apAllocator) noexcept
        : m_pAllocator(apAllocator)
    {
        Allocator::Push(m_pAllocator);
    }

    ScopedAllocator::ScopedAllocator(Allocator& aAllocator) noexcept
        : ScopedAllocator(&aAllocator)
    {
    }

    ScopedAllocator::~ScopedAllocator() noexcept
    {
        Allocator::Pop();
    }

}
