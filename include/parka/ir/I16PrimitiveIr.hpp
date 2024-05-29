#ifndef PARKA_IR_I16_PRIMITIVE_IR_HPP
#define PARKA_IR_I16_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class I16PrimitiveIr: public TypeIr, public LValueIr
	{
		String _symbol;

	public:

		static I16PrimitiveIr instance;

	private:

		I16PrimitiveIr();
		I16PrimitiveIr(I16PrimitiveIr&&) = delete;
		I16PrimitiveIr(const I16PrimitiveIr&) = delete;

	public:
	
		BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const TypeIr&) const;
		AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const TypeIr&) const;

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
