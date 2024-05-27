#include "parka/ir/I64PrimitiveIr.hpp"

namespace parka::ir
{
	I64PrimitiveIr I64PrimitiveIr::instance;

	I64PrimitiveIr::I64PrimitiveIr():
		TypeIr(TypeCategory::I64),
		LValueIr(ResolvableType::Primitive),
		_symbol("i64")
	{}

	std::ostream& I64PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
