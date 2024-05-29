#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	InvalidTypeIr InvalidTypeIr::typeNameType("type name");
	InvalidTypeIr InvalidTypeIr::typeNameType("package");

	InvalidTypeIr::InvalidTypeIr(const char* name):
		TypeIr(TypeCategory::TypeName),
		_symbol(name)
	{}

	std::ostream& InvalidTypeIr::printType(std::ostream& out) const
	{
		out << _symbol;

		return out;
	}
}
