#include "parka/validation/I64TypeContext.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	I64TypeContext I64TypeContext::instance;

	ir::BinaryOperatorIr* I64TypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::Add, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Add, i64, Integer>();
				break;

			case BinaryExpressionType::Subtract:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::Subtract, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Subtract, i64, Integer>();
				break;

			case BinaryExpressionType::Multiply:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::Multiply, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Multiply, i64, Integer>();
				break;

			case BinaryExpressionType::Divide:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::Divide, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Divide, i64, Integer>();
				break;

			case BinaryExpressionType::Modulus:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::Modulus, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Modulus, i64, Integer>();
				break;

			case BinaryExpressionType::BitwiseOr:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::BitwiseOr, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseOr, i64, Integer>();
				break;

			case BinaryExpressionType::BitwiseXor:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::BitwiseXor, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseXor, i64, Integer>();
				break;

			case BinaryExpressionType::BitwiseAnd:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::BitwiseAnd, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseAnd, i64, Integer>();
				break;

			case BinaryExpressionType::LeftShift:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::LeftShift, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LeftShift, i64, Integer>();
				break;

			case BinaryExpressionType::RightShift:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::RightShift, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::RightShift, i64, Integer>();
				break;

			case BinaryExpressionType::LessThan:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::LessThan, i64, i64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThan, i64, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThan:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::GreaterThan, i64, i64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThan, i64, Integer, bool>();
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i64, i64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i64, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i64, i64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i64, Integer, bool>();
				break;


			case BinaryExpressionType::Equals:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::Equals, i64, i64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Equals, i64, Integer, bool>();
				break;

			case BinaryExpressionType::NotEquals:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &binop<BinaryExpressionType::NotEquals, i64, i64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::NotEquals, i64, Integer, bool>();
				break;


			default:
				break;
		}

		return nullptr;
	}

	ir::AssignmentOperatorIr* I64TypeContext::getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const
	{
		switch (assignmentType)
		{
			case AssignmentType::Assign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::Assign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::Assign, i64, Integer>();
				break;

			case AssignmentType::AddAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::AddAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::AddAssign, i64, Integer>();
				break;

			case AssignmentType::SubtractAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::SubtractAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::SubtractAssign, i64, Integer>();
				break;

			case AssignmentType::MultiplyAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::MultiplyAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::MultiplyAssign, i64, Integer>();
				break;

			case AssignmentType::DivideAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::DivideAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::DivideAssign, i64, Integer>();
				break;

			case AssignmentType::ModulusAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::ModulusAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::ModulusAssign, i64, Integer>();
				break;

			case AssignmentType::LeftShiftAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::LeftShiftAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::LeftShiftAssign, i64, Integer>();
				break;

			case AssignmentType::RightShiftAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::RightShiftAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::RightShiftAssign, i64, Integer>();
				break;

			case AssignmentType::BitwiseOrAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::BitwiseOrAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseOrAssign, i64, Integer>();
				break;

			case AssignmentType::BitwiseXorAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::BitwiseXorAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseXorAssign, i64, Integer>();
				break;

			case AssignmentType::BitwiseAndAssign:
				if (other == ir::PrimitiveIr::i64Primitive)
					return &assgn<AssignmentType::BitwiseAndAssign, i64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseAndAssign, i64, Integer>();
				break;
		}
		
		return nullptr;
	}
}
