#ifndef PARKA_IR_INTEGER_PRIMITIVE_IR_HPP
#define PARKA_IR_INTEGER_PRIMITIVE_IR_HPP

#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class IntegerPrimitiveIr: public TypeIr
	{
	public:

		static IntegerPrimitiveIr instance;

	private:
	
		IntegerPrimitiveIr();
		IntegerPrimitiveIr(IntegerPrimitiveIr&&) = default;
		IntegerPrimitiveIr(const IntegerPrimitiveIr&) = delete;

	public:

		ConversionIr* getConversion(const TypeIr& toType) const;
		std::ostream& printType(std::ostream& out) const;
	};
}

#endif
