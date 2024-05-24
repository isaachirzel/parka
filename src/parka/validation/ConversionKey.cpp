#include "parka/validation/ConversionKey.hpp"

namespace parka::validation
{
	ConversionKey::ConversionKey():
		_to(ir::TypeIr::voidType),
		_from(ir::TypeIr::voidType)
	{}

	ConversionKey::ConversionKey(const ir::TypeIr& to, const ir::TypeIr& from):
		_to(to),
		_from(from)
	{}

	bool ConversionKey::operator==(const ConversionKey& other) const
	{
		return _to == other._to && _from == other._from;
	}
}

std::size_t std::hash<parka::validation::ConversionKey>::operator()(const parka::validation::ConversionKey& key) const
{
	auto typeHasher = std::hash<parka::ir::TypeIr>();

	return typeHasher(key._to) ^ typeHasher(key._from);
}
