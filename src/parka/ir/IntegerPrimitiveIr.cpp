#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/I32PrimitiveIr.hpp"

namespace parka::ir
{
	IntegerPrimitiveIr IntegerPrimitiveIr::instance;

	ConversionIr i32Conversion(I32PrimitiveIr::instance, IntegerPrimitiveIr::instance);

	IntegerPrimitiveIr::IntegerPrimitiveIr():
		TypeIr(TypeCategory::Integer)
	{}

	ConversionIr* IntegerPrimitiveIr::getConversion(const TypeIr& toType) const
	{
		if (toType == I32PrimitiveIr::instance)
			return &i32Conversion;

		return nullptr;
	}

	std::ostream& IntegerPrimitiveIr::printType(std::ostream& out) const
	{
		out << "integer";

		return out;
	}
}
