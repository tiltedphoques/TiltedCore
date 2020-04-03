#include "ViewBuffer.hpp"

namespace TiltedPhoques
{
    ViewBuffer::ViewBuffer(uint8_t* apData, size_t aSize) noexcept
    {
        m_pData = apData;
        m_size = aSize;
    }

    ViewBuffer::~ViewBuffer()
    {
        m_pData = nullptr;
    }
}
