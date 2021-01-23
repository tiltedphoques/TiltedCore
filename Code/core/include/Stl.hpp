#pragma once

#include "StlAllocator.hpp"

#include <unordered_set>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <deque>
#include <memory>
#include <string>

namespace TiltedPhoques
{
namespace details
{
    template<class T>
    struct UniqueDeleter
    {
        void operator()(std::conditional_t<std::is_array_v<T>, T, T*> apData)
        {
            TiltedPhoques::Delete<T>(apData);
        }
    };
}
    

    template<class T>
    using Vector = std::vector<T, StlAllocator<T>>;

    template<class T>
    using List = std::list<T, StlAllocator<T>>;

    template<class T, class U>
    using Map = std::unordered_map<T, U, std::hash<T>, std::equal_to<T>, StlAllocator<std::pair<const T, U>>>;

    template<class T>
    using Set = std::unordered_set<T, std::hash<T>, std::equal_to<T>, StlAllocator<T>>;

    template<class T>
    using Deque = std::deque<T, StlAllocator<T>>;

    template<class T>
    using Queue = std::queue<T, Deque<T>>;

    template<class T>
    using UniquePtr = std::unique_ptr<T, details::UniqueDeleter<T>>;

    template<class T>
    using SharedPtr = std::shared_ptr<T>;

    using String = std::basic_string<char, std::char_traits<char>, StlAllocator<char>>;
    using WString = std::basic_string<wchar_t, std::char_traits<wchar_t>, StlAllocator<wchar_t>>;

    template <class T, class U>
    auto CastUnique(UniquePtr<U> aPtr)
    {
        auto pPtr = aPtr.release();

        return UniquePtr<T>(reinterpret_cast<T*>(pPtr));
    }

    template<typename T, typename... Args>
    auto MakeUnique(Args&& ... args)
    {
        return UniquePtr<T>(New<T>(std::forward<Args>(args)...));
    }

    template<typename T, typename... Args>
    auto MakeShared(Args&& ... args)
    {
        return std::allocate_shared<T>(StlAllocator<T>(), std::forward<Args>(args)...);
    }
}

namespace std
{
    template<> struct hash<TiltedPhoques::String>
    {
        std::size_t operator()(const TiltedPhoques::String& aString) const noexcept
        {
            return std::hash<std::string>{}(aString.data());
        }
    };
}
