#ifndef PARKA_VALIDATION_BOOL_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_BOOL_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class BoolTypeContext: public TypeContext
	{
	public:

		static BoolTypeContext instance;

	private:

		BoolTypeContext() = default;
		BoolTypeContext(BoolTypeContext&&) = default;
		BoolTypeContext(const BoolTypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
