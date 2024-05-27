#ifndef PARKA_IR_I32_PRIMITIVE_IR_HPP
#define PARKA_IR_I32_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	class I32PrimitiveIr: public TypeIr, public LValueIr
	{
		String _symbol;

	public:

		static I32PrimitiveIr instance;

	private:

		I32PrimitiveIr();
		I32PrimitiveIr(I32PrimitiveIr&&) = delete;
		I32PrimitiveIr(const I32PrimitiveIr&) = delete;

	public:

		BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const TypeIr&) const;

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return TypeNameIr::instance; }
	};
}

#endif
