#ifndef PARKA_IR_U8_PRIMITIVE_IR_HPP
#define PARKA_IR_U8_PRIMITIVE_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class U8PrimitiveIr: public TypeIr, public EntityIr
	{
		String _symbol;

	public:

		static U8PrimitiveIr instance;

	private:

		U8PrimitiveIr();
		U8PrimitiveIr(U8PrimitiveIr&&) = delete;
		U8PrimitiveIr(const U8PrimitiveIr&) = delete;

	public:

		BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const TypeIr&) const;
		AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const TypeIr&) const;

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
