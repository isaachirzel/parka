#include "parka/ir/VoidPrimitiveIr.hpp"

namespace parka::ir
{
	VoidPrimitiveIr VoidPrimitiveIr::voidPrimitive("void");

	VoidPrimitiveIr::VoidPrimitiveIr(const char *name):
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}
}
