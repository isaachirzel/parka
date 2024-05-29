#include "parka/ir/VoidPrimitiveIr.hpp"

namespace parka::ir
{
	VoidPrimitiveIr VoidPrimitiveIr::instance("void");

	VoidPrimitiveIr::VoidPrimitiveIr(const char *name):
		TypeIr(TypeCategory::Void),
		EntityIr(ResolvableType::Primitive),
		_name(name)
	{}

	std::ostream& VoidPrimitiveIr::printType(std::ostream& out) const
	{
		out << _name;

		return out;
	}
}
