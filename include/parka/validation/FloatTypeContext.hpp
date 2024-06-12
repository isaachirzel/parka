#ifndef PARKA_VALIDATION_FLOAT_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_FLOAT_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class FloatTypeContext: public TypeContext
	{
	public:

		static FloatTypeContext instance;

	private:

		FloatTypeContext() = default;
		FloatTypeContext(FloatTypeContext&&) = default;
		FloatTypeContext(const FloatTypeContext&) = delete;

	public:

		ir::CastIr* getImplicitCastTo(const ir::TypeIr& toType) const;
		ir::CastIr* getExplicitCastTo(const ir::TypeIr& toType) const;
		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const;
	};
}

#endif
