#include "parka/validation/I16TypeContext.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	I16TypeContext I16TypeContext::instance;

	ir::BinaryOperatorIr* I16TypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::Add, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Add, i16, Integer>();
				break;

			case BinaryExpressionType::Subtract:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::Subtract, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Subtract, i16, Integer>();
				break;

			case BinaryExpressionType::Multiply:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::Multiply, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Multiply, i16, Integer>();
				break;

			case BinaryExpressionType::Divide:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::Divide, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Divide, i16, Integer>();
				break;

			case BinaryExpressionType::Modulus:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::Modulus, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Modulus, i16, Integer>();
				break;

			case BinaryExpressionType::BitwiseOr:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::BitwiseOr, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseOr, i16, Integer>();
				break;

			case BinaryExpressionType::BitwiseXor:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::BitwiseXor, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseXor, i16, Integer>();
				break;

			case BinaryExpressionType::BitwiseAnd:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::BitwiseAnd, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseAnd, i16, Integer>();
				break;

			case BinaryExpressionType::LeftShift:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::LeftShift, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LeftShift, i16, Integer>();
				break;

			case BinaryExpressionType::RightShift:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::RightShift, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::RightShift, i16, Integer>();
				break;

			case BinaryExpressionType::LessThan:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::LessThan, i16, i16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThan, i16, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThan:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::GreaterThan, i16, i16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThan, i16, Integer, bool>();
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i16, i16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, i16, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i16, i16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, i16, Integer, bool>();
				break;


			case BinaryExpressionType::Equals:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::Equals, i16, i16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Equals, i16, Integer, bool>();
				break;

			case BinaryExpressionType::NotEquals:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &binop<BinaryExpressionType::NotEquals, i16, i16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::NotEquals, i16, Integer, bool>();
				break;


			default:
				break;
		}

		return nullptr;
	}

	ir::AssignmentOperatorIr* I16TypeContext::getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const
	{
		switch (assignmentType)
		{
			case AssignmentType::Assign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::Assign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::Assign, i16, Integer>();
				break;

			case AssignmentType::AddAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::AddAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::AddAssign, i16, Integer>();
				break;

			case AssignmentType::SubtractAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::SubtractAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::SubtractAssign, i16, Integer>();
				break;

			case AssignmentType::MultiplyAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::MultiplyAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::MultiplyAssign, i16, Integer>();
				break;

			case AssignmentType::DivideAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::DivideAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::DivideAssign, i16, Integer>();
				break;

			case AssignmentType::ModulusAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::ModulusAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::ModulusAssign, i16, Integer>();
				break;

			case AssignmentType::LeftShiftAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::LeftShiftAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::LeftShiftAssign, i16, Integer>();
				break;

			case AssignmentType::RightShiftAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::RightShiftAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::RightShiftAssign, i16, Integer>();
				break;

			case AssignmentType::BitwiseOrAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::BitwiseOrAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseOrAssign, i16, Integer>();
				break;

			case AssignmentType::BitwiseXorAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::BitwiseXorAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseXorAssign, i16, Integer>();
				break;

			case AssignmentType::BitwiseAndAssign:
				if (other == ir::PrimitiveIr::i16Primitive)
					return &assgn<AssignmentType::BitwiseAndAssign, i16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseAndAssign, i16, Integer>();
				break;
		}
		
		return nullptr;
	}
}
