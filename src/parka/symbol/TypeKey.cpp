#include "parka/symbol/TypeKey.hpp"
#include "parka/util/Hash.hpp"

namespace parka
{
	TypeKey::TypeKey(const ir::TypeBaseIr& typeBase):
		_typeBase(&typeBase)
	{}

	bool TypeKey::operator==(const TypeKey& other)
	{
		return _typeBase == other._typeBase;
	}
}

size_t std::hash<parka::TypeKey>::operator()(const parka::TypeKey& key) const
{
	return parka::hashNumber((size_t)key._typeBase);
}
