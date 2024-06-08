#include "parka/validation/BoolTypeContext.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	BoolTypeContext BoolTypeContext::instance;

	ir::BinaryOperatorIr* BoolTypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& rhs) const
	{
		if (&rhs != &ir::PrimitiveIr::boolPrimitive)
			return nullptr;

		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Equals:
				return &binop<BinaryExpressionType::Equals, bool>();

			case BinaryExpressionType::NotEquals:
				return &binop<BinaryExpressionType::NotEquals, bool>();

			case BinaryExpressionType::BooleanOr:
				return &binop<BinaryExpressionType::BooleanOr, bool>();

			case BinaryExpressionType::BooleanAnd:
				return &binop<BinaryExpressionType::BooleanAnd, bool>();

			default:
				break;
		}

		return nullptr;
	}

	ir::AssignmentOperatorIr* BoolTypeContext::getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const
	{
		if (other == ir::PrimitiveIr::boolPrimitive && assignmentType == AssignmentType::Assign)
			return &assgn<AssignmentType::Assign, bool>();

		return nullptr;
	}
}
