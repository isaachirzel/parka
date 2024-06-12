#ifndef PARKA_VALIDATION_INTEGER_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_INTEGER_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class IntegerTypeContext: public TypeContext
	{
	public:

		static IntegerTypeContext instance;
	
	private:

		IntegerTypeContext() = default;
		IntegerTypeContext(IntegerTypeContext&&) = default;
		IntegerTypeContext(const IntegerTypeContext&) = default;

	public:

		ir::CastIr* getImplicitCastTo(const ir::TypeIr&) const;
		ir::CastIr* getExplicitCastTo(const ir::TypeIr&) const;
		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
