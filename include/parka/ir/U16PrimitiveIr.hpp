#ifndef PARKA_IR_U16_PRIMITIVE_IR_HPP
#define PARKA_IR_U16_PRIMITIVE_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class U16PrimitiveIr: public TypeIr, public EntityIr
	{
		String _symbol;

	public:

		static U16PrimitiveIr instance;

	private:

		U16PrimitiveIr();
		U16PrimitiveIr(U16PrimitiveIr&&) = delete;
		U16PrimitiveIr(const U16PrimitiveIr&) = delete;

	public:

		BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const TypeIr&) const;
		AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const TypeIr&) const;

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
