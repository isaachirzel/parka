#ifndef PARKA_IR_U32_PRIMITIVE_IR_HPP
#define PARKA_IR_U32_PRIMITIVE_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class U32PrimitiveIr: public TypeIr, public EntityIr
	{
		String _symbol;

	public:

		static U32PrimitiveIr instance;

	private:

		U32PrimitiveIr();
		U32PrimitiveIr(U32PrimitiveIr&&) = delete;
		U32PrimitiveIr(const U32PrimitiveIr&) = delete;

	public:

		BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const TypeIr&) const;
		AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const TypeIr&) const;

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
