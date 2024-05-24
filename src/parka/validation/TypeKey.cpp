#include "parka/validation/TypeKey.hpp"
#include "parka/util/Hash.hpp"

namespace parka::validation
{
	TypeKey::TypeKey(const ir::TypeBaseIr& typeBase):
		_typeBase(&typeBase)
	{}

	bool TypeKey::operator==(const TypeKey& other)
	{
		return _typeBase == other._typeBase;
	}
}

size_t std::hash<parka::validation::TypeKey>::operator()(const parka::validation::TypeKey& key) const
{
	return parka::hashNumber((size_t)key._typeBase);
}
