#ifndef PARKA_VALIDATION_I16_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_I16_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class I16TypeContext: public TypeContext
	{
	public:

		static I16TypeContext instance;

	private:

		I16TypeContext() = default;
		I16TypeContext(I16TypeContext&&) = default;
		I16TypeContext(const I16TypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;
	};
}

#endif
