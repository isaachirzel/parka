#include "parka/ir/I16PrimitiveIr.hpp"
#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/util/AssignmentOperatorUtil.hpp"
#include "parka/util/BinaryOperatorUtil.hpp"

namespace parka::ir
{
	I16PrimitiveIr I16PrimitiveIr::instance;

	I16PrimitiveIr::I16PrimitiveIr():
		TypeIr(TypeCategory::I16),
		LValueIr(ResolvableType::Primitive),
		_symbol("i16")
	{}

	BinaryOperatorIr* I16PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				if (other == *this)
					return &binop<BinaryExpressionType::Add, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Add, i16, Integer>();
				break;

			case BinaryExpressionType::Subtract:
				if (other == *this)
					return &binop<BinaryExpressionType::Subtract, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Subtract, i16, Integer>();
				break;

			case BinaryExpressionType::Multiply:
				if (other == *this)
					return &binop<BinaryExpressionType::Multiply, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Multiply, i16, Integer>();
				break;

			case BinaryExpressionType::Divide:
				if (other == *this)
					return &binop<BinaryExpressionType::Divide, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Divide, i16, Integer>();
				break;

			case BinaryExpressionType::Modulus:
				if (other == *this)
					return &binop<BinaryExpressionType::Modulus, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Modulus, i16, Integer>();
				break;

			case BinaryExpressionType::BitwiseOr:
				if (other == *this)
					return &binop<BinaryExpressionType::BitwiseOr, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::BitwiseOr, i16, Integer>();
				break;

			case BinaryExpressionType::BitwiseXor:
				if (other == *this)
					return &binop<BinaryExpressionType::BitwiseXor, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::BitwiseXor, i16, Integer>();
				break;

			case BinaryExpressionType::BitwiseAnd:
				if (other == *this)
					return &binop<BinaryExpressionType::BitwiseAnd, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::BitwiseAnd, i16, Integer>();
				break;

			case BinaryExpressionType::LeftShift:
				if (other == *this)
					return &binop<BinaryExpressionType::LeftShift, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::LeftShift, i16, Integer>();
				break;

			case BinaryExpressionType::RightShift:
				if (other == *this)
					return &binop<BinaryExpressionType::RightShift, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::RightShift, i16, Integer>();
				break;

			case BinaryExpressionType::LessThan:
				if (other == *this)
					return &binop<BinaryExpressionType::LessThan, i16, i16, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::LessThan, i16, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThan:
				if (other == *this)
					return &binop<BinaryExpressionType::GreaterThan, i16, i16, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::GreaterThan, i16, Integer, bool>();
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if (other == *this)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i16, i16, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i16, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if (other == *this)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i16, i16, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i16, Integer, bool>();
				break;


			case BinaryExpressionType::Equals:
				if (other == *this)
					return &binop<BinaryExpressionType::Equals, i16, i16, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::Equals, i16, Integer, bool>();
				break;

			case BinaryExpressionType::NotEquals:
				if (other == *this)
					return &binop<BinaryExpressionType::NotEquals, i16, i16, bool>();

				if (other == IntegerPrimitiveIr::instance)
					return &binop<BinaryExpressionType::NotEquals, i16, Integer, bool>();
				break;


			default:
				break;
		}

		return nullptr;
	}

	AssignmentOperatorIr* I16PrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	{
		switch (assignmentType)
		{
			case AssignmentType::Assign:
				if (other == *this)
					return &assgn<AssignmentType::Assign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::Assign, i16, Integer>();
				break;

			case AssignmentType::AddAssign:
				if (other == *this)
					return &assgn<AssignmentType::AddAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::AddAssign, i16, Integer>();
				break;

			case AssignmentType::SubtractAssign:
				if (other == *this)
					return &assgn<AssignmentType::SubtractAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::SubtractAssign, i16, Integer>();
				break;

			case AssignmentType::MultiplyAssign:
				if (other == *this)
					return &assgn<AssignmentType::MultiplyAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::MultiplyAssign, i16, Integer>();
				break;

			case AssignmentType::DivideAssign:
				if (other == *this)
					return &assgn<AssignmentType::DivideAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::DivideAssign, i16, Integer>();
				break;

			case AssignmentType::ModulusAssign:
				if (other == *this)
					return &assgn<AssignmentType::ModulusAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::ModulusAssign, i16, Integer>();
				break;

			case AssignmentType::LeftShiftAssign:
				if (other == *this)
					return &assgn<AssignmentType::LeftShiftAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::LeftShiftAssign, i16, Integer>();
				break;

			case AssignmentType::RightShiftAssign:
				if (other == *this)
					return &assgn<AssignmentType::RightShiftAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::RightShiftAssign, i16, Integer>();
				break;

			case AssignmentType::BitwiseOrAssign:
				if (other == *this)
					return &assgn<AssignmentType::BitwiseOrAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::BitwiseOrAssign, i16, Integer>();
				break;

			case AssignmentType::BitwiseXorAssign:
				if (other == *this)
					return &assgn<AssignmentType::BitwiseXorAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::BitwiseXorAssign, i16, Integer>();
				break;

			case AssignmentType::BitwiseAndAssign:
				if (other == *this)
					return &assgn<AssignmentType::BitwiseAndAssign, i16>();

				if (other == IntegerPrimitiveIr::instance)
					return &assgn<AssignmentType::BitwiseAndAssign, i16, Integer>();
				break;
		}
		
		return nullptr;
	}

	std::ostream& I16PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;
		return out;
	}
}
