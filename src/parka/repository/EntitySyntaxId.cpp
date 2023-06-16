// #include "parka/repository/EntityAstId.hpp"

// namespace parka
// {
// 	std::ostream& operator<<(std::ostream& out, const EntityAstId& id)
// 	{

// 		out << id._type << "s[" << id._index << ']';

// 		return out;
// 	}

// 	bool EntityAstId::operator==(const EntityAstId& other) const
// 	{
// 		return _type == other._type && _index == other._index;
// 	}
// }

// namespace std
// {
// 	using namespace parka;

// 	usize hash<EntityAstId>::operator()(const EntityAstId& key) const
// 	{
// 		auto seed = (u64)key._index  | ((u64)key._type << 32);
// 		auto hash = std::hash<usize>{}(seed);

// 		return hash;
// 	}
// }
