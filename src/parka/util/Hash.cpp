#include "parka/util/Hash.hpp"

namespace parka
{
	constexpr u32 u32HashConstant	= 0x045d9f3b;
	constexpr u64 u64HashConstantA	= 0xbf58476d1ce4e5b9;
	constexpr u64 u64HashConstantB	= 0x94d049bb133111eb;

	template <>
	u32 hash32(const u32& value)
	{
		u32 hash = value;

		hash = ((hash >> 16) ^ hash) * u32HashConstant;
		hash = ((hash >> 16) ^ hash) * u32HashConstant;
		hash = (hash >> 16) ^ hash;

		return hash;
	}

	template <>
	u64 hash64(const u64& value)
	{
		u64 hash = value;

		hash = (hash ^ (hash >> 30)) * u64HashConstantA;
		hash = (hash ^ (hash >> 27)) * u64HashConstantB;
		hash = hash ^ (hash >> 31);

		return hash;
	}
}
