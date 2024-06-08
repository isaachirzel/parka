#ifndef PARKA_VALIDATION_U8_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_U8_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class U8TypeContext: public TypeContext
	{
	public:

		static U8TypeContext instance;

	private:

		U8TypeContext() = default;
		U8TypeContext(U8TypeContext&&) = default;
		U8TypeContext(const U8TypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
