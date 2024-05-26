#include "parka/ir/I32PrimitiveIr.hpp"
#include "parka/ir/LValueIr.hpp"
namespace parka::ir
{
	I32PrimitiveIr I32PrimitiveIr::instance;

	I32PrimitiveIr::I32PrimitiveIr():
		TypeIr(TypeCategory::I32),
		LValueIr(ResolvableType::Primitive),
		_symbol("i32")
	{}
	
	std::ostream& I32PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;

		return out;
	}
}
