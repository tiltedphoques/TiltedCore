#pragma once

#include <cstdint>
#include "Allocator.h"

class Buffer : public AllocatorCompatible
{
public:

    Buffer();
    explicit Buffer(size_t aSize);
    Buffer(const Buffer& acBuffer);
    Buffer(Buffer&& aBuffer) noexcept;
    virtual ~Buffer();

    uint8_t operator[](size_t aIndex) const;
    uint8_t& operator[](size_t aIndex);

    Buffer& operator=(const Buffer& acBuffer);
    Buffer& operator=(Buffer&& aBuffer) noexcept;

    [[nodiscard]] size_t GetSize() const;

    [[nodiscard]] const uint8_t* GetData() const;
    [[nodiscard]] uint8_t* GetWriteData();

    struct Cursor
    {
        explicit Cursor(Buffer* apBuffer);

        void Reset();
        bool Eof() const;
        void Advance(size_t aByteCount);
        void Reverse(size_t aByteCount);

        [[nodiscard]] size_t GetBytePosition() const;
        [[nodiscard]] size_t GetBitPosition() const;

    protected:

        size_t m_bitPosition;
        Buffer* m_pBuffer;
    };

    struct Reader : Cursor
    {
        explicit Reader(Buffer* apBuffer);

        bool ReadBits(uint64_t& aDestination, size_t aCount);
        bool ReadBytes(uint8_t* apDestination, size_t aCount);
    };

    struct Writer : Cursor
    {
        explicit Writer(Buffer* apBuffer);

        bool WriteBits(uint64_t aData, size_t aCount);
        bool WriteBytes(const uint8_t* apSource, size_t aCount);
    };

private:

    uint8_t* m_pData;
    size_t m_size;
};
