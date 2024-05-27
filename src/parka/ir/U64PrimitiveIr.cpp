
#include "parka/ir/U64PrimitiveIr.hpp"

namespace parka::ir
{
	U64PrimitiveIr U64PrimitiveIr::instance;

	U64PrimitiveIr::U64PrimitiveIr():
		TypeIr(TypeCategory::U64),
		LValueIr(ResolvableType::Primitive),
		_symbol("u64")
	{}

	std::ostream& U64PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
