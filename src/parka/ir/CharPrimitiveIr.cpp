#include "parka/ir/PrimitiveIr.hpp"

namespace parka::ir
{
	
	// BinaryOperatorIr* PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	// {
	// 	if (other != *this)
	// 		return nullptr;

	// 	switch (binaryExpressionType)
	// 	{
	// 		case BinaryExpressionType::Equals:
	// 			return &binop<BinaryExpressionType::Equals, char>();

	// 		case BinaryExpressionType::NotEquals:
	// 			return &binop<BinaryExpressionType::NotEquals, char>();
			
	// 		default:
	// 			break;
	// 	}

	// 	return nullptr;
	// }

	// AssignmentOperatorIr* PrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	// {
	// 	if (other == *this && assignmentType == AssignmentType::Assign)
	// 		return &assgn<AssignmentType::Assign, char>();
		
	// 	return nullptr;
	// }
}
