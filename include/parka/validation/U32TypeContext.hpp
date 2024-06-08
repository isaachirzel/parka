#ifndef PARKA_VALIDATION_U32_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_U32_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class U32TypeContext: public TypeContext
	{
	public:

		static U32TypeContext instance;

	private:

		U32TypeContext() = default;
		U32TypeContext(U32TypeContext&&) = default;
		U32TypeContext(const U32TypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
