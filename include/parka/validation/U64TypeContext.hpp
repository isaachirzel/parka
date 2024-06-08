#ifndef PARKA_VALIDATION_U64_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_U64_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class U64TypeContext: public TypeContext
	{
	public:

		static U64TypeContext instance;

	private:

		U64TypeContext() = default;
		U64TypeContext(U64TypeContext&&) = default;
		U64TypeContext(const U64TypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
