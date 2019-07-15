#include "ScratchAllocator.h"
#include <Platform.h>
#include <memory>


ScratchAllocator::ScratchAllocator(size_t aSize)
    : m_size(aSize)
{
    m_pBaseData = m_pData = GetDefault()->Allocate(aSize);

    if (m_pData == nullptr)
    {
        m_size = 0;
    }
}

ScratchAllocator::~ScratchAllocator()
{
    GetDefault()->Free(m_pBaseData);
}

void* ScratchAllocator::Allocate(size_t aSize)
{
    if (std::align(alignof(std::max_align_t), aSize, m_pData, m_size))
    {
        const auto pResult = m_pData;
        m_pData = static_cast<char*>(m_pData) + aSize;
        m_size -= aSize;
        return pResult;
    }

    return nullptr;
}

void ScratchAllocator::Free(void* apData)
{
    TP_UNUSED(apData);
}

size_t ScratchAllocator::Size(void* apData)
{
    TP_UNUSED(apData);
    return m_size;
}