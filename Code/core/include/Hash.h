#pragma once

#include <cstdint>

namespace FHash
{
    uint64_t Crc64(const unsigned char* acpData, size_t aLength);
}