#include "parka/ir/StringPrimitiveIr.hpp"

namespace parka::ir
{
	StringPrimitiveIr StringPrimitiveIr::stringPrimitive("string");

	StringPrimitiveIr::StringPrimitiveIr(const char *name):
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}
}
