#include "parka/ast/type/type_id.hpp"
#include "parka/util/hash.hpp"

constexpr u32 first4Bits	= 0x0000000F;
constexpr u32 first28Bits	= 0x0FFFFFFF;

template <>
u32 hash32(const TypeId& id)
{
	auto seed = ((u32)id.type() & first4Bits) + ((id.index() & first28Bits) << 4);
	auto hash = hash32(seed);

	return hash;
}

template <>
u64 hash64(const TypeId& id)
{
	auto seed = (u64)id.index()  | ((u64)id.type() << 32);
	auto hash = hash64(seed);

	return hash;
}

bool operator==(const TypeId& left, const TypeId& right)
{
	return left._type == right._type
		&& left._index == right._index;
}
