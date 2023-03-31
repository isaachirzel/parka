#include "parka/ast/type/type_key.hpp"
#include "parka/util/hash.hpp"
#include "parka/util/print.hpp"

template <>
u64 hash64(const TypeKey& key)
{
	return hash64(key.id());
}

usize std::hash<TypeKey>::operator()(const TypeKey& key) const
{
	return hash64(key);
}

bool operator==(const TypeKey& left, const TypeKey& right)
{
	return left._id == right._id;
}
