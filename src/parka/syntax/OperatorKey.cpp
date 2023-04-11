#include "parka/syntax/OperatorKey.hpp"
#include "parka/util/Hash.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	u64 hash64(const OperatorKey& key)
	{
		auto hash = hash64((u64)key.operatorType());

		hash ^= hash64(key.leftKey());
		hash ^= hash64(key.rightKey());

		return hash;
	}

	bool operator==(const OperatorKey& left, const OperatorKey& right)
	{
		return left._operatorType == right._operatorType
			&& left._leftKey == right._leftKey
			&& left._rightKey == right._rightKey;
	}
}
