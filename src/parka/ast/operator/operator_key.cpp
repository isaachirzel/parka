#include "parka/ast/operator/operator_key.hpp"
#include "parka/util/hash.hpp"
#include "parka/util/print.hpp"

u64 hash64(const OperatorKey& key)
{
	auto hash = hash64((u64)key.operatorType());

	hash ^= hash64(key.leftKey());
	hash ^= hash64(key.rightKey());

	return hash;
}

usize std::hash<OperatorKey>::operator()(const OperatorKey& key) const
{
	return hash64(key);
}

bool operator==(const OperatorKey& left, const OperatorKey& right)
{
	return left._operatorType == right._operatorType
		&& left._leftKey == right._leftKey
		&& left._rightKey == right._rightKey;
}
