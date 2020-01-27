#include "Allocator.hpp"
#include "MimallocAllocator.hpp"
#include <cassert>

namespace TiltedPhoques
{
    struct AllocatorStack
    {
        enum
        {
            kMaxAllocatorCount = 1024
        };

        AllocatorStack() noexcept
            : m_index(0)
        {
            m_stack[0] = Allocator::GetDefault();
        }

        void Push(Allocator* apAllocator) noexcept
        {
            assert(m_index + 1 < kMaxAllocatorCount);

            m_index++;
            m_stack[m_index] = apAllocator;
        }

        Allocator* Pop() noexcept
        {
            assert(m_index > 0);

            const auto pAllocator = m_stack[m_index];
            m_index--;

            return pAllocator;
        }

        [[nodiscard]] Allocator* Get() noexcept
        {
            return m_stack[m_index];
        }

        [[nodiscard]] static AllocatorStack& Instance() noexcept
        {
            static thread_local AllocatorStack s_stack;
            return s_stack;
        }

    private:

        uint32_t m_index;
        Allocator* m_stack[kMaxAllocatorCount]{};
    };


    void Allocator::Push(Allocator* apAllocator) noexcept
    {
        AllocatorStack::Instance().Push(apAllocator);
    }

    void Allocator::Push(Allocator& aAllocator) noexcept
    {
        Push(&aAllocator);
    }

    Allocator* Allocator::Pop() noexcept
    {
        return AllocatorStack::Instance().Pop();
    }

    Allocator* Allocator::Get() noexcept
    {
        return AllocatorStack::Instance().Get();
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
