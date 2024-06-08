#include "parka/validation/I32TypeContext.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	I32TypeContext I32TypeContext::instance;

	ir::BinaryOperatorIr* I32TypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Add, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Add, i32, Integer>();
				break;

			case BinaryExpressionType::Subtract:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Subtract, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Subtract, i32, Integer>();
				break;

			case BinaryExpressionType::Multiply:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Multiply, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Multiply, i32, Integer>();
				break;

			case BinaryExpressionType::Divide:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Divide, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Divide, i32, Integer>();
				break;

			case BinaryExpressionType::Modulus:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Modulus, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Modulus, i32, Integer>();
				break;

			case BinaryExpressionType::BitwiseOr:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::BitwiseOr, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseOr, i32, Integer>();
				break;

			case BinaryExpressionType::BitwiseXor:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::BitwiseXor, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseXor, i32, Integer>();
				break;

			case BinaryExpressionType::BitwiseAnd:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::BitwiseAnd, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseAnd, i32, Integer>();
				break;

			case BinaryExpressionType::LeftShift:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::LeftShift, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LeftShift, i32, Integer>();
				break;

			case BinaryExpressionType::RightShift:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::RightShift, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::RightShift, i32, Integer>();
				break;

			case BinaryExpressionType::LessThan:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::LessThan, i32, i32, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThan, i32, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThan:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::GreaterThan, i32, i32, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThan, i32, Integer, bool>();
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i32, i32, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i32, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i32, i32, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i32, Integer, bool>();
				break;


			case BinaryExpressionType::Equals:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::Equals, i32, i32, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Equals, i32, Integer, bool>();
				break;

			case BinaryExpressionType::NotEquals:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &binop<BinaryExpressionType::NotEquals, i32, i32, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::NotEquals, i32, Integer, bool>();
				break;


			default:
				break;
		}

		return nullptr;
	}

	ir::AssignmentOperatorIr* I32TypeContext::getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const
	{
		switch (assignmentType)
		{
			case AssignmentType::Assign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::Assign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::Assign, i32, Integer>();
				break;

			case AssignmentType::AddAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::AddAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::AddAssign, i32, Integer>();
				break;

			case AssignmentType::SubtractAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::SubtractAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::SubtractAssign, i32, Integer>();
				break;

			case AssignmentType::MultiplyAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::MultiplyAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::MultiplyAssign, i32, Integer>();
				break;

			case AssignmentType::DivideAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::DivideAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::DivideAssign, i32, Integer>();
				break;

			case AssignmentType::ModulusAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::ModulusAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::ModulusAssign, i32, Integer>();
				break;

			case AssignmentType::LeftShiftAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::LeftShiftAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::LeftShiftAssign, i32, Integer>();
				break;

			case AssignmentType::RightShiftAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::RightShiftAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::RightShiftAssign, i32, Integer>();
				break;

			case AssignmentType::BitwiseOrAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::BitwiseOrAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseOrAssign, i32, Integer>();
				break;

			case AssignmentType::BitwiseXorAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::BitwiseXorAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseXorAssign, i32, Integer>();
				break;

			case AssignmentType::BitwiseAndAssign:
				if (other == ir::PrimitiveIr::i32Primitive)
					return &assgn<AssignmentType::BitwiseAndAssign, i32>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseAndAssign, i32, Integer>();
				break;
		}
		
		return nullptr;
	}
}
