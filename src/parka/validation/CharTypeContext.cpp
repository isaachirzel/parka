#include "parka/validation/CharTypeContext.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	CharTypeContext CharTypeContext::instance;

	ir::BinaryOperatorIr* CharTypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const
	{
		if (other != ir::PrimitiveIr::boolPrimitive)
			return nullptr;

		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Equals:
				return &binop<BinaryExpressionType::Equals, char>();

			case BinaryExpressionType::NotEquals:
				return &binop<BinaryExpressionType::NotEquals, char>();
			
			default:
				break;
		}

		return nullptr;
	}

	ir::AssignmentOperatorIr* CharTypeContext::getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const
	{
		if (other == ir::PrimitiveIr::charPrimitive && assignmentType == AssignmentType::Assign)
			return &assgn<AssignmentType::Assign, char>();
		
		return nullptr;
	}
}
