#ifndef PARKA_VALIDATION_F64_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_F64_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class F64TypeContext: public TypeContext
	{
	public:

		static F64TypeContext instance;

	private:

		F64TypeContext() = default;
		F64TypeContext(F64TypeContext&&) = default;
		F64TypeContext(const F64TypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
