#include "parka/ir/I8PrimitiveIr.hpp"
#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/util/AssignmentOperatorUtil.hpp"
#include "parka/util/BinaryOperatorUtil.hpp"

namespace parka::ir
{
	I8PrimitiveIr I8PrimitiveIr::instance;

	I8PrimitiveIr::I8PrimitiveIr():
		TypeIr(TypeCategory::I8),
		EntityIr(ResolvableType::Primitive),
		_symbol("i8")
	{}

	BinaryOperatorIr* I8PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				if (other == *this)
					return &binop<BinaryExpressionType::Add, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Add, i8, Integer>();
				break;

			case BinaryExpressionType::Subtract:
				if (other == *this)
					return &binop<BinaryExpressionType::Subtract, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Subtract, i8, Integer>();
				break;

			case BinaryExpressionType::Multiply:
				if (other == *this)
					return &binop<BinaryExpressionType::Multiply, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Multiply, i8, Integer>();
				break;

			case BinaryExpressionType::Divide:
				if (other == *this)
					return &binop<BinaryExpressionType::Divide, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Divide, i8, Integer>();
				break;

			case BinaryExpressionType::Modulus:
				if (other == *this)
					return &binop<BinaryExpressionType::Modulus, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Modulus, i8, Integer>();
				break;

			case BinaryExpressionType::BitwiseOr:
				if (other == *this)
					return &binop<BinaryExpressionType::BitwiseOr, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::BitwiseOr, i8, Integer>();
				break;

			case BinaryExpressionType::BitwiseXor:
				if (other == *this)
					return &binop<BinaryExpressionType::BitwiseXor, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::BitwiseXor, i8, Integer>();
				break;

			case BinaryExpressionType::BitwiseAnd:
				if (other == *this)
					return &binop<BinaryExpressionType::BitwiseAnd, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::BitwiseAnd, i8, Integer>();
				break;

			case BinaryExpressionType::LeftShift:
				if (other == *this)
					return &binop<BinaryExpressionType::LeftShift, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::LeftShift, i8, Integer>();
				break;

			case BinaryExpressionType::RightShift:
				if (other == *this)
					return &binop<BinaryExpressionType::RightShift, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::RightShift, i8, Integer>();
				break;

			case BinaryExpressionType::LessThan:
				if (other == *this)
					return &binop<BinaryExpressionType::LessThan, i8, i8, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::LessThan, i8, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThan:
				if (other == *this)
					return &binop<BinaryExpressionType::GreaterThan, i8, i8, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::GreaterThan, i8, Integer, bool>();
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if (other == *this)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i8, i8, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i8, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if (other == *this)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i8, i8, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i8, Integer, bool>();
				break;


			case BinaryExpressionType::Equals:
				if (other == *this)
					return &binop<BinaryExpressionType::Equals, i8, i8, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Equals, i8, Integer, bool>();
				break;

			case BinaryExpressionType::NotEquals:
				if (other == *this)
					return &binop<BinaryExpressionType::NotEquals, i8, i8, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::NotEquals, i8, Integer, bool>();
				break;


			default:
				break;
		}

		return nullptr;
	}

	AssignmentOperatorIr* I8PrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	{
		switch (assignmentType)
		{
			case AssignmentType::Assign:
				if (other == *this)
					return &assgn<AssignmentType::Assign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::Assign, i8, Integer>();
				break;

			case AssignmentType::AddAssign:
				if (other == *this)
					return &assgn<AssignmentType::AddAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::AddAssign, i8, Integer>();
				break;

			case AssignmentType::SubtractAssign:
				if (other == *this)
					return &assgn<AssignmentType::SubtractAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::SubtractAssign, i8, Integer>();
				break;

			case AssignmentType::MultiplyAssign:
				if (other == *this)
					return &assgn<AssignmentType::MultiplyAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::MultiplyAssign, i8, Integer>();
				break;

			case AssignmentType::DivideAssign:
				if (other == *this)
					return &assgn<AssignmentType::DivideAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::DivideAssign, i8, Integer>();
				break;

			case AssignmentType::ModulusAssign:
				if (other == *this)
					return &assgn<AssignmentType::ModulusAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::ModulusAssign, i8, Integer>();
				break;

			case AssignmentType::LeftShiftAssign:
				if (other == *this)
					return &assgn<AssignmentType::LeftShiftAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::LeftShiftAssign, i8, Integer>();
				break;

			case AssignmentType::RightShiftAssign:
				if (other == *this)
					return &assgn<AssignmentType::RightShiftAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::RightShiftAssign, i8, Integer>();
				break;

			case AssignmentType::BitwiseOrAssign:
				if (other == *this)
					return &assgn<AssignmentType::BitwiseOrAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::BitwiseOrAssign, i8, Integer>();
				break;

			case AssignmentType::BitwiseXorAssign:
				if (other == *this)
					return &assgn<AssignmentType::BitwiseXorAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::BitwiseXorAssign, i8, Integer>();
				break;

			case AssignmentType::BitwiseAndAssign:
				if (other == *this)
					return &assgn<AssignmentType::BitwiseAndAssign, i8>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::BitwiseAndAssign, i8, Integer>();
				break;
		}
		
		return nullptr;
	}

	std::ostream& I8PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
