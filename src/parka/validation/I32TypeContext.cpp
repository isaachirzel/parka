#include "parka/validation/I32TypeContext.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/util/AssignmentOperatorUtil.hpp"
#include "parka/util/BinaryOperatorUtil.hpp"

namespace parka::validation
{
	using namespace ir;

	I32TypeContext I32TypeContext::instance;

	BinaryOperatorIr* I32TypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& other) const
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Add, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Add, i32, Integer>();
				break;

			case BinaryExpressionType::Subtract:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Subtract, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Subtract, i32, Integer>();
				break;

			case BinaryExpressionType::Multiply:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Multiply, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Multiply, i32, Integer>();
				break;

			case BinaryExpressionType::Divide:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Divide, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Divide, i32, Integer>();
				break;

			case BinaryExpressionType::Modulus:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Modulus, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Modulus, i32, Integer>();
				break;

			case BinaryExpressionType::BitwiseOr:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::BitwiseOr, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseOr, i32, Integer>();
				break;

			case BinaryExpressionType::BitwiseXor:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::BitwiseXor, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseXor, i32, Integer>();
				break;

			case BinaryExpressionType::BitwiseAnd:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::BitwiseAnd, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseAnd, i32, Integer>();
				break;

			case BinaryExpressionType::LeftShift:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::LeftShift, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LeftShift, i32, Integer>();
				break;

			case BinaryExpressionType::RightShift:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::RightShift, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::RightShift, i32, Integer>();
				break;

			case BinaryExpressionType::LessThan:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::LessThan, i32, i32, bool>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThan, i32, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThan:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::GreaterThan, i32, i32, bool>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThan, i32, Integer, bool>();
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i32, i32, bool>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i32, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i32, i32, bool>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i32, Integer, bool>();
				break;


			case BinaryExpressionType::Equals:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Equals, i32, i32, bool>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Equals, i32, Integer, bool>();
				break;

			case BinaryExpressionType::NotEquals:
				if (other == PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::NotEquals, i32, i32, bool>();

				if (other == PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::NotEquals, i32, Integer, bool>();
				break;


			default:
				break;
		}

		return nullptr;
	}

	AssignmentOperatorIr* I32TypeContext::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	{
		switch (assignmentType)
		{
			case AssignmentType::Assign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::Assign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::Assign, i32, Integer>();
				break;

			case AssignmentType::AddAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::AddAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::AddAssign, i32, Integer>();
				break;

			case AssignmentType::SubtractAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::SubtractAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::SubtractAssign, i32, Integer>();
				break;

			case AssignmentType::MultiplyAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::MultiplyAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::MultiplyAssign, i32, Integer>();
				break;

			case AssignmentType::DivideAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::DivideAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::DivideAssign, i32, Integer>();
				break;

			case AssignmentType::ModulusAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::ModulusAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::ModulusAssign, i32, Integer>();
				break;

			case AssignmentType::LeftShiftAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::LeftShiftAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::LeftShiftAssign, i32, Integer>();
				break;

			case AssignmentType::RightShiftAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::RightShiftAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::RightShiftAssign, i32, Integer>();
				break;

			case AssignmentType::BitwiseOrAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::BitwiseOrAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseOrAssign, i32, Integer>();
				break;

			case AssignmentType::BitwiseXorAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::BitwiseXorAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseXorAssign, i32, Integer>();
				break;

			case AssignmentType::BitwiseAndAssign:
				if (other == PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::BitwiseAndAssign, i32>();

				if (other == PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseAndAssign, i32, Integer>();
				break;
		}
		
		return nullptr;
	}
}
