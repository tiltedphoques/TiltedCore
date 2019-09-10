#pragma once

#include "Allocator.hpp"

namespace TiltedPhoques
{
    struct StandardAllocator : Allocator
    {
        StandardAllocator() noexcept = default;
        virtual ~StandardAllocator() = default;

        TP_NOCOPYMOVE(StandardAllocator);

        [[nodiscard]] void* Allocate(size_t aSize) noexcept override;
        void Free(void* apData) noexcept override;
        [[nodiscard]] size_t Size(void* apData) noexcept override;
    };
}
