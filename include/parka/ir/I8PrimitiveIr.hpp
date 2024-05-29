#ifndef PARKA_IR_I8_PRIMITIVE_IR_HPP
#define PARKA_IR_I8_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class I8PrimitiveIr: public TypeIr, public LValueIr
	{
		String _symbol;

	public:

		static I8PrimitiveIr instance;

	private:

		I8PrimitiveIr();
		I8PrimitiveIr(I8PrimitiveIr&&) = delete;
		I8PrimitiveIr(const I8PrimitiveIr&) = delete;

	public:

		BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const TypeIr&) const;
		AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const TypeIr&) const;

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
