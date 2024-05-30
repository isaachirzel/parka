#include "parka/ir/PrimitiveIr.hpp"

namespace parka::ir
{
	// BinaryOperatorIr* PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	// {
	// 	switch (binaryExpressionType)
	// 	{
	// 		case BinaryExpressionType::Add:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Add, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Add, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Subtract:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Subtract, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Subtract, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Multiply:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Multiply, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Multiply, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Divide:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Divide, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Divide, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Modulus:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Modulus, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Modulus, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseOr:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseOr, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::BitwiseOr, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseXor:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseXor, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::BitwiseXor, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseAnd:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LeftShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LeftShift, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::LeftShift, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::RightShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::RightShift, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::RightShift, u8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LessThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThan, u8, u8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::LessThan, u8, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThan, u8, u8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::GreaterThan, u8, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::LessThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, u8, u8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, u8, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u8, u8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u8, Integer, bool>();
	// 			break;


	// 		case BinaryExpressionType::Equals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Equals, u8, u8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Equals, u8, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::NotEquals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::NotEquals, u8, u8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::NotEquals, u8, Integer, bool>();
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
	// 				return &assgn<AssignmentType::Assign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::Assign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::AddAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::AddAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::AddAssign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::SubtractAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::SubtractAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::SubtractAssign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::MultiplyAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::MultiplyAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::MultiplyAssign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::DivideAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::DivideAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::DivideAssign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::ModulusAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::ModulusAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::ModulusAssign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::LeftShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::LeftShiftAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::LeftShiftAssign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::RightShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::RightShiftAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::RightShiftAssign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseOrAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseXorAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, u8, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseAndAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, u8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, u8, Integer>();
	// 			break;
	// 	}
		
	// 	return nullptr;
	// }
}
