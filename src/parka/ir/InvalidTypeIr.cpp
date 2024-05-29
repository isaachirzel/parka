#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	InvalidTypeIr InvalidTypeIr::typeNameType("type name");
	InvalidTypeIr InvalidTypeIr::packageType("package");
	InvalidTypeIr InvalidTypeIr::functionType("function");

	InvalidTypeIr::InvalidTypeIr(const char* name):
		TypeIr(TypeCategory::Invalid),
		_symbol(name)
	{}

	std::ostream& InvalidTypeIr::printType(std::ostream& out) const
	{
		out << _symbol;

		return out;
	}
}
