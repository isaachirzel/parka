#include "parka/ir/I16PrimitiveIr.hpp"

namespace parka::ir
{
	I16PrimitiveIr I16PrimitiveIr::instance;

	I16PrimitiveIr::I16PrimitiveIr():
		TypeIr(TypeCategory::I16),
		LValueIr(ResolvableType::Primitive),
		_symbol("i16")
	{}

	std::ostream& I16PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
