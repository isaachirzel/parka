#include "parka/validation/ConversionKey.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/util/Hash.hpp"

namespace parka::validation
{
	ConversionKey::ConversionKey():
		_to(&ir::PrimitiveIr::voidPrimitive),
		_from(&ir::PrimitiveIr::voidPrimitive)
	{}

	ConversionKey::ConversionKey(const ir::TypeIr& to, const ir::TypeIr& from):
		_to(&to),
		_from(&from)
	{}

	bool ConversionKey::operator==(const ConversionKey& other) const
	{
		return _to == other._to && _from == other._from;
	}
}

std::size_t std::hash<parka::validation::ConversionKey>::operator()(const parka::validation::ConversionKey& key) const
{
	return parka::hashNumber((size_t)key._to ^ (size_t)key._from);
}
