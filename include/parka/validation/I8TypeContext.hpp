#ifndef PARKA_VALIDATION_I8_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_I8_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class I8TypeContext: public TypeContext
	{
	public:

		static I8TypeContext instance;

	private:

		I8TypeContext() = default;
		I8TypeContext(I8TypeContext&&) = default;
		I8TypeContext(const I8TypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
