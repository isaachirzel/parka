#include "parka/ir/BoolPrimitiveIr.hpp"

namespace parka::ir
{
	BoolPrimitiveIr BoolPrimitiveIr::boolPrimitive("bool");

	BoolPrimitiveIr::BoolPrimitiveIr(const char *name):
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}

	std::ostream& BoolPrimitiveIr::printType(std::ostream& out) const
	{
		out << _name;

		return out;
	}
}
