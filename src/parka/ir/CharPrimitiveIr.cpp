#include "parka/ir/CharPrimitiveIr.hpp"

namespace parka::ir
{
	CharPrimitiveIr CharPrimitiveIr::charPrimitive("char");

	CharPrimitiveIr::CharPrimitiveIr(const char *name):
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}
}
