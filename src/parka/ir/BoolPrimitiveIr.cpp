#include "parka/ir/BoolPrimitiveIr.hpp"

namespace parka::ir
{
	BoolPrimitiveIr BoolPrimitiveIr::boolPrimitive("bool");

	BoolPrimitiveIr::BoolPrimitiveIr(const char *name):
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}
}
