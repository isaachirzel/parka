#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	TypeNameIr TypeNameIr::instance;

	TypeNameIr::TypeNameIr():
		TypeIr(TypeCategory::TypeName),
		_symbol("type name")
	{}

	std::ostream& TypeNameIr::printType(std::ostream& out) const
	{
		out << _symbol;

		return out;
	}
}
