#ifndef WARLER_UTIL_TABLE_HPP
#define WARLER_UTIL_TABLE_HPP

#include "parka/util/string.hpp"

#include <unordered_map>

template <typename Key, typename Value>
using Table = std::unordered_map<Key, Value>;

#endif
