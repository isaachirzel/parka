#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/I32PrimitiveIr.hpp"
#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/ir/EntityIr.hpp"
#include "parka/util/AssignmentOperatorUtil.hpp"
#include "parka/util/BinaryOperatorUtil.hpp"
#include "parka/util/Integer.hpp"

namespace parka::ir
{
	I32PrimitiveIr I32PrimitiveIr::instance;

	I32PrimitiveIr::I32PrimitiveIr():
		TypeIr(TypeCategory::I32),
		EntityIr(ResolvableType::Primitive),
		_symbol("i32")
	{}
	
	// BinaryOperatorIr* I32PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	// {
	// 	switch (binaryExpressionType)
	// 	{
	// 		case BinaryExpressionType::Add:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Add, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Add, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Subtract:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Subtract, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Subtract, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Multiply:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Multiply, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Multiply, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Divide:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Divide, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Divide, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Modulus:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Modulus, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Modulus, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseOr:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseOr, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::BitwiseOr, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseXor:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseXor, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::BitwiseXor, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseAnd:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LeftShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LeftShift, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::LeftShift, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::RightShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::RightShift, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::RightShift, i32, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LessThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThan, i32, i32, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::LessThan, i32, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThan, i32, i32, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::GreaterThan, i32, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::LessThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, i32, i32, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, i32, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i32, i32, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i32, Integer, bool>();
	// 			break;


	// 		case BinaryExpressionType::Equals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Equals, i32, i32, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Equals, i32, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::NotEquals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::NotEquals, i32, i32, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::NotEquals, i32, Integer, bool>();
	// 			break;


	// 		default:
	// 			break;
	// 	}

	// 	return nullptr;
	// }

	// AssignmentOperatorIr* I32PrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	// {
	// 	switch (assignmentType)
	// 	{
	// 		case AssignmentType::Assign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::Assign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::Assign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::AddAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::AddAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::AddAssign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::SubtractAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::SubtractAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::SubtractAssign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::MultiplyAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::MultiplyAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::MultiplyAssign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::DivideAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::DivideAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::DivideAssign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::ModulusAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::ModulusAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::ModulusAssign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::LeftShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::LeftShiftAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::LeftShiftAssign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::RightShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::RightShiftAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::RightShiftAssign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseOrAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseXorAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, i32, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseAndAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, i32>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, i32, Integer>();
	// 			break;
	// 	}
		
	// 	return nullptr;
	// }

	std::ostream& I32PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;

		return out;
	}
}
