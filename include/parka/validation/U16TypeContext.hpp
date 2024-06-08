#ifndef PARKA_VALIDATION_U16_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_U16_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class U16TypeContext: public TypeContext
	{
	public:

		static U16TypeContext instance;

	private:

		U16TypeContext() = default;
		U16TypeContext(U16TypeContext&&) = default;
		U16TypeContext(const U16TypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
