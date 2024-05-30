
#include "parka/ir/U16PrimitiveIr.hpp"
#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/util/AssignmentOperatorUtil.hpp"
#include "parka/util/BinaryOperatorUtil.hpp"

namespace parka::ir
{
	U16PrimitiveIr U16PrimitiveIr::instance;

	U16PrimitiveIr::U16PrimitiveIr():
		TypeIr(TypeCategory::U16),
		EntityIr(ResolvableType::Primitive),
		_symbol("u16")
	{}

	// BinaryOperatorIr* U16PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	// {
	// 	switch (binaryExpressionType)
	// 	{
	// 		case BinaryExpressionType::Add:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Add, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Add, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Subtract:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Subtract, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Subtract, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Multiply:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Multiply, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Multiply, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Divide:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Divide, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Divide, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::Modulus:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Modulus, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Modulus, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseOr:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseOr, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::BitwiseOr, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseXor:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseXor, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::BitwiseXor, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::BitwiseAnd:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::BitwiseAnd, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LeftShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LeftShift, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::LeftShift, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::RightShift:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::RightShift, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::RightShift, u16, Integer>();
	// 			break;

	// 		case BinaryExpressionType::LessThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThan, u16, u16, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::LessThan, u16, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThan:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThan, u16, u16, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::GreaterThan, u16, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::LessThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, u16, u16, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::LessThanOrEqualTo, u16, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::GreaterThanOrEqualTo:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u16, u16, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u16, Integer, bool>();
	// 			break;


	// 		case BinaryExpressionType::Equals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::Equals, u16, u16, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::Equals, u16, Integer, bool>();
	// 			break;

	// 		case BinaryExpressionType::NotEquals:
	// 			if (other == *this)
	// 				return &binop<BinaryExpressionType::NotEquals, u16, u16, bool>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &binop<BinaryExpressionType::NotEquals, u16, Integer, bool>();
	// 			break;


	// 		default:
	// 			break;
	// 	}

	// 	return nullptr;
	// }

	// AssignmentOperatorIr* U16PrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	// {
	// 	switch (assignmentType)
	// 	{
	// 		case AssignmentType::Assign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::Assign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::Assign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::AddAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::AddAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::AddAssign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::SubtractAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::SubtractAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::SubtractAssign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::MultiplyAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::MultiplyAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::MultiplyAssign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::DivideAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::DivideAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::DivideAssign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::ModulusAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::ModulusAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::ModulusAssign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::LeftShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::LeftShiftAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::LeftShiftAssign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::RightShiftAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::RightShiftAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::RightShiftAssign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseOrAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::BitwiseOrAssign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseXorAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::BitwiseXorAssign, u16, Integer>();
	// 			break;

	// 		case AssignmentType::BitwiseAndAssign:
	// 			if (other == *this)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, u16>();

	// 			if (other == IntegerPrimitiveIr::instance)
	// 				return &assgn<AssignmentType::BitwiseAndAssign, u16, Integer>();
	// 			break;
	// 	}
		
	// 	return nullptr;
	// }

	std::ostream& U16PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
