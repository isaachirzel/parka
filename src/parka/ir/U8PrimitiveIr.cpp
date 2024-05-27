#include "parka/ir/U8PrimitiveIr.hpp"

namespace parka::ir
{
	U8PrimitiveIr U8PrimitiveIr::instance;

	U8PrimitiveIr::U8PrimitiveIr():
		TypeIr(TypeCategory::U8),
		LValueIr(ResolvableType::Primitive),
		_symbol("u8")
	{}

	std::ostream& U8PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
