#include "parka/ir/StringPrimitiveIr.hpp"

namespace parka::ir
{
	StringPrimitiveIr StringPrimitiveIr::stringPrimitive("string");

	StringPrimitiveIr::StringPrimitiveIr(const char *name):
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}

	std::ostream& StringPrimitiveIr::printType(std::ostream& out) const
	{
		out << _name;

		return out;
	}
}
