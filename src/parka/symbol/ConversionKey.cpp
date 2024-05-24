#include "parka/symbol/ConversionKey.hpp"

namespace parka
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
