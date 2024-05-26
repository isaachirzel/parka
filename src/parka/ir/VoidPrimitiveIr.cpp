#include "parka/ir/VoidPrimitiveIr.hpp"

namespace parka::ir
{
	VoidPrimitiveIr VoidPrimitiveIr::voidPrimitive("void");

	VoidPrimitiveIr::VoidPrimitiveIr(const char *name):
		TypeIr(TypeCategory::Void),
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}

	std::ostream& VoidPrimitiveIr::printType(std::ostream& out) const
	{
		out << _name;

		return out;
	}
}
