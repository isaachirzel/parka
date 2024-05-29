
#include "parka/ir/U32PrimitiveIr.hpp"
#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/util/AssignmentOperatorUtil.hpp"
#include "parka/util/BinaryOperatorUtil.hpp"

namespace parka::ir
{
	U32PrimitiveIr U32PrimitiveIr::instance;

	U32PrimitiveIr::U32PrimitiveIr():
		TypeIr(TypeCategory::U32),
		EntityIr(ResolvableType::Primitive),
		_symbol("u32")
	{}

	BinaryOperatorIr* U32PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				if (other == *this)
					return &binop<BinaryExpressionType::Add, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Add, u32, Integer>();
				break;

			case BinaryExpressionType::Subtract:
				if (other == *this)
					return &binop<BinaryExpressionType::Subtract, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Subtract, u32, Integer>();
				break;

			case BinaryExpressionType::Multiply:
				if (other == *this)
					return &binop<BinaryExpressionType::Multiply, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Multiply, u32, Integer>();
				break;

			case BinaryExpressionType::Divide:
				if (other == *this)
					return &binop<BinaryExpressionType::Divide, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Divide, u32, Integer>();
				break;

			case BinaryExpressionType::Modulus:
				if (other == *this)
					return &binop<BinaryExpressionType::Modulus, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Modulus, u32, Integer>();
				break;

			case BinaryExpressionType::BitwiseOr:
				if (other == *this)
					return &binop<BinaryExpressionType::BitwiseOr, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::BitwiseOr, u32, Integer>();
				break;

			case BinaryExpressionType::BitwiseXor:
				if (other == *this)
					return &binop<BinaryExpressionType::BitwiseXor, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::BitwiseXor, u32, Integer>();
				break;

			case BinaryExpressionType::BitwiseAnd:
				if (other == *this)
					return &binop<BinaryExpressionType::BitwiseAnd, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::BitwiseAnd, u32, Integer>();
				break;

			case BinaryExpressionType::LeftShift:
				if (other == *this)
					return &binop<BinaryExpressionType::LeftShift, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::LeftShift, u32, Integer>();
				break;

			case BinaryExpressionType::RightShift:
				if (other == *this)
					return &binop<BinaryExpressionType::RightShift, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::RightShift, u32, Integer>();
				break;

			case BinaryExpressionType::LessThan:
				if (other == *this)
					return &binop<BinaryExpressionType::LessThan, u32, u32, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::LessThan, u32, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThan:
				if (other == *this)
					return &binop<BinaryExpressionType::GreaterThan, u32, u32, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::GreaterThan, u32, Integer, bool>();
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if (other == *this)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, u32, u32, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, u32, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if (other == *this)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u32, u32, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u32, Integer, bool>();
				break;


			case BinaryExpressionType::Equals:
				if (other == *this)
					return &binop<BinaryExpressionType::Equals, u32, u32, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Equals, u32, Integer, bool>();
				break;

			case BinaryExpressionType::NotEquals:
				if (other == *this)
					return &binop<BinaryExpressionType::NotEquals, u32, u32, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::NotEquals, u32, Integer, bool>();
				break;


			default:
				break;
		}

		return nullptr;
	}

	AssignmentOperatorIr* U32PrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	{
		switch (assignmentType)
		{
			case AssignmentType::Assign:
				if (other == *this)
					return &assgn<AssignmentType::Assign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::Assign, u32, Integer>();
				break;

			case AssignmentType::AddAssign:
				if (other == *this)
					return &assgn<AssignmentType::AddAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::AddAssign, u32, Integer>();
				break;

			case AssignmentType::SubtractAssign:
				if (other == *this)
					return &assgn<AssignmentType::SubtractAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::SubtractAssign, u32, Integer>();
				break;

			case AssignmentType::MultiplyAssign:
				if (other == *this)
					return &assgn<AssignmentType::MultiplyAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::MultiplyAssign, u32, Integer>();
				break;

			case AssignmentType::DivideAssign:
				if (other == *this)
					return &assgn<AssignmentType::DivideAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::DivideAssign, u32, Integer>();
				break;

			case AssignmentType::ModulusAssign:
				if (other == *this)
					return &assgn<AssignmentType::ModulusAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::ModulusAssign, u32, Integer>();
				break;

			case AssignmentType::LeftShiftAssign:
				if (other == *this)
					return &assgn<AssignmentType::LeftShiftAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::LeftShiftAssign, u32, Integer>();
				break;

			case AssignmentType::RightShiftAssign:
				if (other == *this)
					return &assgn<AssignmentType::RightShiftAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::RightShiftAssign, u32, Integer>();
				break;

			case AssignmentType::BitwiseOrAssign:
				if (other == *this)
					return &assgn<AssignmentType::BitwiseOrAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::BitwiseOrAssign, u32, Integer>();
				break;

			case AssignmentType::BitwiseXorAssign:
				if (other == *this)
					return &assgn<AssignmentType::BitwiseXorAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::BitwiseXorAssign, u32, Integer>();
				break;

			case AssignmentType::BitwiseAndAssign:
				if (other == *this)
					return &assgn<AssignmentType::BitwiseAndAssign, u32>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::BitwiseAndAssign, u32, Integer>();
				break;
		}
		
		return nullptr;
	}

	std::ostream& U32PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
