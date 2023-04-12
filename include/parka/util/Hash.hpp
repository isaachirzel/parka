#ifndef PARKA_UTIL_HASH_HPP
#define PARKA_UTIL_HASH_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	template <typename T>
	u32 hash32(const T& value);
	
	template <typename T>
	u64 hash64(const T& value);

	template <>
	u32 hash32(const u32& value);

	template <>
	u64 hash64(const u64& value);
}

#endif
