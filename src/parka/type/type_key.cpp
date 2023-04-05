#include "parka/type/type_key.hpp"
#include "parka/util/hash.hpp"
#include "parka/util/print.hpp"

template <>
u64 hash64(const TypeKey& key)
{
	return hash64(key.id());
}

bool operator==(const TypeKey& left, const TypeKey& right)
{
	return left._id == right._id;
}
