#ifndef PARKA_VALIDATION_F32_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_F32_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class F32TypeContext: public TypeContext
	{
	public:

		static F32TypeContext instance;

	private:

		F32TypeContext() = default;
		F32TypeContext(F32TypeContext&&) = default;
		F32TypeContext(const F32TypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
