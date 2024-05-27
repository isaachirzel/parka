#include "parka/ir/CharPrimitiveIr.hpp"

namespace parka::ir
{
	CharPrimitiveIr CharPrimitiveIr::instance;

	CharPrimitiveIr::CharPrimitiveIr():
		TypeIr(TypeCategory::Char),
		LValueIr(ResolvableType::Primitive),
		_symbol("char")
	{}

	std::ostream& CharPrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;

		return out;
	}
}
