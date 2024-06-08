#ifndef PARKA_VALIDATION_CHAR_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_CHAR_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class CharTypeContext: public TypeContext
	{
	public:

		static CharTypeContext instance;

	private:

		CharTypeContext() = default;
		CharTypeContext(CharTypeContext&&) = default;
		CharTypeContext(const CharTypeContext&) = delete;

	public:

		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const;
	};
}

#endif
