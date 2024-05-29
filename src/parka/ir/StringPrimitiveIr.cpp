#include "parka/ir/StringPrimitiveIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	StringPrimitiveIr StringPrimitiveIr::instance("string");

	StringPrimitiveIr::StringPrimitiveIr(const char *name):
		TypeIr(TypeCategory::String),
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}

	std::ostream& StringPrimitiveIr::printType(std::ostream& out) const
	{
		out << _name;

		return out;
	}
}
