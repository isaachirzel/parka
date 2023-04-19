#include "parka/repository/TypeId.hpp"

namespace parka
{
	bool operator==(const TypeId& left, const TypeId& right)
	{
		return left._type == right._type
			&& left._index == right._index;
	}
}

namespace std
{
	using namespace parka;

	usize hash<TypeId>::operator()(const TypeId& key) const 
	{
		auto seed = (u64)key.index()  | ((u64)key.type() << 32);
		auto hash = std::hash<usize>{}(seed);

		return hash;
	}
}
