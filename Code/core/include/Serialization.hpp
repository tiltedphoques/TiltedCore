#pragma once

#include <Buffer.hpp>

namespace TiltedPhoques
{
    struct Serialization
    {
        static std::string ReadString(Buffer::Reader& aReader);
        static void WriteString(Buffer::Writer& aWriter, const std::string& acString);

        static uint64_t ReadVarInt(Buffer::Reader& aReader);
        static void WriteVarInt(Buffer::Writer& aWriter, uint64_t aValue);

        static bool ReadBool(Buffer::Reader& aReader);
        static void WriteBool(Buffer::Writer& aWriter, bool aValue);

        static double ReadDouble(Buffer::Reader& aReader);
        static void WriteDouble(Buffer::Writer& aWriter, double aValue);
    };
}
