#ifndef PARKA_VALIDATION_I64_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_I64_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class I64TypeContext: public TypeContext
	{
	public:

		static I64TypeContext instance;

	private:

		I64TypeContext() = default;
		I64TypeContext(I64TypeContext&&) = default;
		I64TypeContext(const I64TypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
