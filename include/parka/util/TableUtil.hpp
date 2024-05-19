#ifndef PARKA_UTIL_TABLE_UTIL_HPP
#define PARKA_UTIL_TABLE_UTIL_HPP

#include "parka/util/Common.hpp"

namespace parka::table
{
	constexpr usize empty = -1;

	extern const usize primeNumbers[];
	extern const usize primeNumberCount;

	usize getCapacity(usize minimumCapacity);
}

#endif
