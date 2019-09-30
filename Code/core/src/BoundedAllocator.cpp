#include "BoundedAllocator.hpp"

namespace TiltedPhoques
{
    BoundedAllocator::BoundedAllocator(const size_t aMaximumAllocationSize) noexcept
        : m_availableMemory{ aMaximumAllocationSize }
    {
    }

    void* BoundedAllocator::Allocate(size_t aSize) noexcept
    {
        if (m_availableMemory >= aSize)
        {
            m_availableMemory -= aSize;
            return StandardAllocator::Allocate(aSize);
        }

        return nullptr;
    }

    void BoundedAllocator::Free(void* apData) noexcept
    {
        m_availableMemory += Size(apData);

        StandardAllocator::Free(apData);
    }
}
