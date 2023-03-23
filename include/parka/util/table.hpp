#ifndef WARLER_UTIL_TABLE_HPP
#define WARLER_UTIL_TABLE_HPP

#include "parka/util/string.hpp"

#include <unordered_map>

template <typename T>
using Table = std::unordered_map<String, T>;

#endif
