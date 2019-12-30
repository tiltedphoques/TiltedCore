#pragma once

#include "Meta.hpp"

#define TP_ALLOCATOR                                                                    \
    void SetAllocator(Allocator* apAllocator) noexcept { m_pAllocator = apAllocator; }  \
    TiltedPhoques::Allocator* GetAllocator() noexcept { return m_pAllocator; }          \
private:                                                                                \
    TiltedPhoques::Allocator* m_pAllocator{ TiltedPhoques::Allocator::Get() };          \
public:

namespace TiltedPhoques
{
    namespace details
    {
        template<typename T>
        using has_get_allocator_t = decltype(std::declval<T&>().GetAllocator());

        template<typename T>
        using has_set_allocator_t = decltype(std::declval<T&>().SetAllocator(nullptr));

        template<typename T>
        constexpr bool has_allocator = is_detected_v<has_get_allocator_t, T>&& is_detected_v<has_set_allocator_t, T>;
    }

    struct Allocator
    {
        virtual ~Allocator() = default;
        [[nodiscard]] virtual void* Allocate(size_t aSize) noexcept  = 0;
        virtual void Free(void* apData) noexcept  = 0;
        [[nodiscard]] virtual size_t Size(void* apData) noexcept = 0;

        template<class T>
        [[nodiscard]] T* New() noexcept
        {
            static_assert(alignof(T) <= alignof(details::default_align_t));

            auto pData = static_cast<T*>(Allocate(sizeof(T)));
            if (pData)
            {
                return new (pData) T();
            }

            return nullptr;
        }

        template<class T, class... Args>
        [[nodiscard]] T* New(Args... args) noexcept
        {
            static_assert(alignof(T) <= alignof(details::default_align_t));

            auto pData = static_cast<T*>(Allocate(sizeof(T)));
            if (pData)
            {
                return new (pData) T(std::forward<Args>(args)...);
            }

            return nullptr;
        }

        template<class T>
        void Delete(T* apData) noexcept
        {
            if (apData == nullptr)
                return;

            apData->~T();
            Free(apData);
        }

        static void Push(Allocator* apAllocator) noexcept;
        static void Push(Allocator& aAllocator) noexcept;
        static Allocator* Pop() noexcept;
        static Allocator* Get() noexcept;
        static Allocator* GetDefault() noexcept;
    };

    struct AllocatorCompatible
    {
        TP_ALLOCATOR
    };


    struct ScopedAllocator
    {
        explicit ScopedAllocator(Allocator* apAllocator) noexcept;
        explicit ScopedAllocator(Allocator& aAllocator) noexcept;
        ~ScopedAllocator() noexcept;

        TP_NOCOPYMOVE(ScopedAllocator);

    private:
        Allocator* m_pAllocator;
    };

    template<class T>
    [[nodiscard]] T* New() noexcept
    {
        if constexpr (details::has_allocator<T>)
            return Allocator::Get()->New<T>();
        else
            return Allocator::GetDefault()->New<T>();
    }

    template<class T, class... Args>
    [[nodiscard]] T* New(Args... args) noexcept
    {
        if constexpr (details::has_allocator<T>)
            return Allocator::Get()->New<T>(std::forward<Args>(args)...);
        else
            return Allocator::GetDefault()->New<T>(std::forward<Args>(args)...);
    }

    template<class T>
    void Delete(T* apEntry) noexcept
    {
        if constexpr (details::has_allocator<T>)
        {
            apEntry->GetAllocator()->Delete(apEntry);
        }
        else
        {
            Allocator::GetDefault()->Delete(apEntry);
        }
    }
}
