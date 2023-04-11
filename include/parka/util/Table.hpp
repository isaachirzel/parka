#ifndef WARLER_UTIL_TABLE_HPP
#define WARLER_UTIL_TABLE_HPP

#include <unordered_map>

namespace parka
{
	template <typename Key, typename Value>
	using Table = std::unordered_map<Key, Value>;
}

#endif
