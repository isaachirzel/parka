
#include "parka/ir/PrimitiveIr.hpp"

namespace parka::ir
{
	// BinaryOperatorIr* PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	// {
	// 	switch (binaryExpressionType)
	// 	{
	// 		case BinaryExpressionType::Add:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Add, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Add, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Subtract:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Subtract, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Subtract, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Multiply:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Multiply, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Multiply, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Divide:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Divide, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Divide, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Modulus:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Modulus, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Modulus, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseOr:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseOr, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::BitwiseOr, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseXor:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseXor, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::BitwiseXor, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseAnd:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LeftShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LeftShift, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::LeftShift, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::RightShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::RightShift, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::RightShift, u64, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LessThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThan, u64, u64, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::LessThan, u64, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThan, u64, u64, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::GreaterThan, u64, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::LessThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, u64, u64, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, u64, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u64, u64, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u64, Integer, bool>();
	// 			break;


	// 		case BinaryExpressionType::Equals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Equals, u64, u64, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Equals, u64, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::NotEquals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::NotEquals, u64, u64, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::NotEquals, u64, Integer, bool>();
	// 			break;


	// 		default:
	// 			break;
	// 	}

	// 	return nullptr;
	// }

	// AssignmentOperatorIr* PrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	// {
	// 	switch (assignmentType)
	// 	{
	// 		case AssignmentType::Assign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::Assign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::Assign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::AddAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::AddAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::AddAssign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::SubtractAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::SubtractAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::SubtractAssign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::MultiplyAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::MultiplyAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::MultiplyAssign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::DivideAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::DivideAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::DivideAssign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::ModulusAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::ModulusAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::ModulusAssign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::LeftShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::LeftShiftAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::LeftShiftAssign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::RightShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::RightShiftAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::RightShiftAssign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseOrAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseXorAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, u64, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseAndAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, u64>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, u64, Integer>();
	// 			break;
	// 	}
		
	// 	return nullptr;
	// }
}