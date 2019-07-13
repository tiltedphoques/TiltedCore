#pragma once

#include "StlAllocator.h"

#include <unordered_set>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>

template<class T>
using Vector = std::vector<T, StlAllocator<T>>;

template<class T>
using List = std::list<T, StlAllocator<T>>;

template<class T>
using Map = std::unordered_map<T, StlAllocator<T>>;

template<class T>
using Set = std::unordered_set<T, StlAllocator<T>>;

template<class T>
using Queue = std::queue<T, StlAllocator<T>>;

template<class T>
using UniquePtr = std::unique_ptr<T, decltype(&Delete<T>)>;

template<typename T, typename... Args>
auto MakeUnique(Args&& ... args)
{
    return UniquePtr<T>(New<T>(std::forward<Args>(args)...), &Delete<T>);
}