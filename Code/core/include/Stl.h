#pragma once

#include "StlAllocator.h"

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