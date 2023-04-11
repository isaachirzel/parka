#include "parka/type/TypeKey.hpp"
#include "parka/util/Hash.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	template <>
	u64 hash64(const TypeKey& key)
	{
		return hash64(key.id());
	}

	bool operator==(const TypeKey& left, const TypeKey& right)
	{
		return left._id == right._id;
	}
}
