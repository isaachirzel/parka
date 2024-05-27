#include "parka/ir/I8PrimitiveIr.hpp"

namespace parka::ir
{
	I8PrimitiveIr I8PrimitiveIr::instance;

	I8PrimitiveIr::I8PrimitiveIr():
		TypeIr(TypeCategory::I8),
		LValueIr(ResolvableType::Primitive),
		_symbol("i8")
	{}

	std::ostream& I8PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
