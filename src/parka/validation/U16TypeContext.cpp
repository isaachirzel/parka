#include "parka/validation/U16TypeContext.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	U16TypeContext U16TypeContext::instance;

	ir::BinaryOperatorIr* U16TypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::Add, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Add, u16, Integer>();
				break;

			case BinaryExpressionType::Subtract:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::Subtract, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Subtract, u16, Integer>();
				break;

			case BinaryExpressionType::Multiply:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::Multiply, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Multiply, u16, Integer>();
				break;

			case BinaryExpressionType::Divide:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::Divide, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Divide, u16, Integer>();
				break;

			case BinaryExpressionType::Modulus:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::Modulus, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Modulus, u16, Integer>();
				break;

			case BinaryExpressionType::BitwiseOr:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::BitwiseOr, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseOr, u16, Integer>();
				break;

			case BinaryExpressionType::BitwiseXor:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::BitwiseXor, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseXor, u16, Integer>();
				break;

			case BinaryExpressionType::BitwiseAnd:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::BitwiseAnd, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseAnd, u16, Integer>();
				break;

			case BinaryExpressionType::LeftShift:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::LeftShift, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LeftShift, u16, Integer>();
				break;

			case BinaryExpressionType::RightShift:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::RightShift, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::RightShift, u16, Integer>();
				break;

			case BinaryExpressionType::LessThan:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::LessThan, u16, u16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThan, u16, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThan:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::GreaterThan, u16, u16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThan, u16, Integer, bool>();
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, u16, u16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, u16, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u16, u16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u16, Integer, bool>();
				break;


			case BinaryExpressionType::Equals:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::Equals, u16, u16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Equals, u16, Integer, bool>();
				break;

			case BinaryExpressionType::NotEquals:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &binop<BinaryExpressionType::NotEquals, u16, u16, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::NotEquals, u16, Integer, bool>();
				break;


			default:
				break;
		}

		return nullptr;
	}

	ir::AssignmentOperatorIr* U16TypeContext::getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const
	{
		switch (assignmentType)
		{
			case AssignmentType::Assign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::Assign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::Assign, u16, Integer>();
				break;

			case AssignmentType::AddAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::AddAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::AddAssign, u16, Integer>();
				break;

			case AssignmentType::SubtractAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::SubtractAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::SubtractAssign, u16, Integer>();
				break;

			case AssignmentType::MultiplyAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::MultiplyAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::MultiplyAssign, u16, Integer>();
				break;

			case AssignmentType::DivideAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::DivideAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::DivideAssign, u16, Integer>();
				break;

			case AssignmentType::ModulusAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::ModulusAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::ModulusAssign, u16, Integer>();
				break;

			case AssignmentType::LeftShiftAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::LeftShiftAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::LeftShiftAssign, u16, Integer>();
				break;

			case AssignmentType::RightShiftAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::RightShiftAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::RightShiftAssign, u16, Integer>();
				break;

			case AssignmentType::BitwiseOrAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::BitwiseOrAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseOrAssign, u16, Integer>();
				break;

			case AssignmentType::BitwiseXorAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::BitwiseXorAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseXorAssign, u16, Integer>();
				break;

			case AssignmentType::BitwiseAndAssign:
				if (other == ir::PrimitiveIr::u16Primitive)
					return &assgn<AssignmentType::BitwiseAndAssign, u16>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseAndAssign, u16, Integer>();
				break;
		}
		
		return nullptr;
	}
}
