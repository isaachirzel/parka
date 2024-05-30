#include "parka/ir/PrimitiveIr.hpp"

namespace parka::ir
{
	// BinaryOperatorIr* PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	// {
	// 	switch (binaryExpressionType)
	// 	{
	// 		case BinaryExpressionType::Add:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Add, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Add, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Subtract:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Subtract, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Subtract, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Multiply:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Multiply, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Multiply, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Divide:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Divide, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Divide, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Modulus:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Modulus, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Modulus, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseOr:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseOr, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::BitwiseOr, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseXor:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseXor, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::BitwiseXor, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseAnd:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LeftShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LeftShift, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::LeftShift, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::RightShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::RightShift, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::RightShift, i8, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LessThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThan, i8, i8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::LessThan, i8, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThan, i8, i8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::GreaterThan, i8, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::LessThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, i8, i8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, i8, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i8, i8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i8, Integer, bool>();
	// 			break;


	// 		case BinaryExpressionType::Equals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Equals, i8, i8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::Equals, i8, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::NotEquals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::NotEquals, i8, i8, bool>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &binop<BinaryExpressionType::NotEquals, i8, Integer, bool>();
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
	// 				return &assgn<AssignmentType::Assign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::Assign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::AddAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::AddAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::AddAssign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::SubtractAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::SubtractAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::SubtractAssign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::MultiplyAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::MultiplyAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::MultiplyAssign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::DivideAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::DivideAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::DivideAssign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::ModulusAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::ModulusAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::ModulusAssign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::LeftShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::LeftShiftAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::LeftShiftAssign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::RightShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::RightShiftAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::RightShiftAssign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseOrAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseXorAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, i8, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseAndAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, i8>();

	// 			if (other == PrimitiveIr::integerPrimitive)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, i8, Integer>();
	// 			break;
	// 	}
		
	// 	return nullptr;
	// }
}
