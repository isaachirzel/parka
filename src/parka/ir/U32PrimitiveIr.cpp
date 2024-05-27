
#include "parka/ir/U32PrimitiveIr.hpp"

namespace parka::ir
{
	U32PrimitiveIr U32PrimitiveIr::instance;

	U32PrimitiveIr::U32PrimitiveIr():
		TypeIr(TypeCategory::U32),
		LValueIr(ResolvableType::Primitive),
		_symbol("u32")
	{}

	std::ostream& U32PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
