#include "parka/ir/F64PrimitiveIr.hpp"
#include "parka/enum/TypeCategory.hpp"
#include "parka/ir/LValueIr.hpp"
namespace parka::ir
{
	F64PrimitiveIr F64PrimitiveIr::instance;
	
	F64PrimitiveIr::F64PrimitiveIr():
		TypeIr(TypeCategory::F64),
		LValueIr(ResolvableType::Primitive),
		_symbol("f64")
	{}

	std::ostream& F64PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
