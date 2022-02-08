#ifndef WARBLER_UTIL_SET_HPP
#define WARBLER_UTIL_SET_HPP

#include <unordered_set>

namespace warbler
{
	template<typename T>
	using Set = std::unordered_set<T>;
}

#endif
