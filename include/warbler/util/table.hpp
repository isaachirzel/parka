#ifndef WARBLER_UTIL_TABLE_HPP
#define WARBLER_UTIL_TABLE_HPP

#include <string>
#include <unordered_map>

namespace warbler
{
	template <typename T>
	using Table = std::unordered_map<std::string, T>;
}

#endif
