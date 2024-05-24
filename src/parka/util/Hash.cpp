#include "parka/util/Hash.hpp"

namespace parka
{
	size_t hashNumber(size_t value)
	{
		value ^= value >> 33;
		value *= 0xff51afd7ed558ccdL;
		value ^= value >> 33;
		value *= 0xc4ceb9fe1a85ec53L;
		value ^= value >> 33;

		return value;
	}
}
