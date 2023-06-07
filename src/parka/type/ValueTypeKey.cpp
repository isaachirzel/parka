#include "parka/symbol/TypeKey.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	bool operator==(const TypeKey& left, const TypeKey& right)
	{
		return left._id == right._id;
	}
}

namespace std
{
	using namespace parka;

	usize hash<TypeKey>::operator()(const TypeKey& key) const
	{
		return hash<TypeId>{}(key.id());
	}
}
