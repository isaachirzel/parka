
#include "parka/ir/U16PrimitiveIr.hpp"

namespace parka::ir
{
	U16PrimitiveIr U16PrimitiveIr::instance;

	U16PrimitiveIr::U16PrimitiveIr():
		TypeIr(TypeCategory::U16),
		LValueIr(ResolvableType::Primitive),
		_symbol("u16")
	{}

	std::ostream& U16PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
