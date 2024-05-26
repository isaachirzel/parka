#include "parka/ir/CharPrimitiveIr.hpp"

namespace parka::ir
{
	CharPrimitiveIr CharPrimitiveIr::charPrimitive("char");

	CharPrimitiveIr::CharPrimitiveIr(const char *name):
		TypeIr(TypeCategory::Char),
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}

	std::ostream& CharPrimitiveIr::printType(std::ostream& out) const
	{
		out << _name;

		return out;
	}
}
