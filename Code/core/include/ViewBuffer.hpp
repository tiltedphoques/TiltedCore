#pragma once

#include "Buffer.hpp"

namespace TiltedPhoques
{
    struct ViewBuffer : Buffer
    {
        explicit ViewBuffer(uint8_t* apData, size_t aSize) noexcept;
        virtual ~ViewBuffer();
    };
}
