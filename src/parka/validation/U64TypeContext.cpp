#include "parka/validation/U64TypeContext.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	U64TypeContext U64TypeContext::instance;
	
	ir::BinaryOperatorIr* U64TypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::Add, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Add, u64, Integer>();
				break;

			case BinaryExpressionType::Subtract:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::Subtract, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Subtract, u64, Integer>();
				break;

			case BinaryExpressionType::Multiply:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::Multiply, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Multiply, u64, Integer>();
				break;

			case BinaryExpressionType::Divide:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::Divide, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Divide, u64, Integer>();
				break;

			case BinaryExpressionType::Modulus:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::Modulus, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Modulus, u64, Integer>();
				break;

			case BinaryExpressionType::BitwiseOr:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::BitwiseOr, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseOr, u64, Integer>();
				break;

			case BinaryExpressionType::BitwiseXor:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::BitwiseXor, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseXor, u64, Integer>();
				break;

			case BinaryExpressionType::BitwiseAnd:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::BitwiseAnd, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::BitwiseAnd, u64, Integer>();
				break;

			case BinaryExpressionType::LeftShift:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::LeftShift, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LeftShift, u64, Integer>();
				break;

			case BinaryExpressionType::RightShift:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::RightShift, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::RightShift, u64, Integer>();
				break;

			case BinaryExpressionType::LessThan:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::LessThan, u64, u64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThan, u64, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThan:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::GreaterThan, u64, u64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThan, u64, Integer, bool>();
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, u64, u64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::LessThanOrEqualTo, u64, Integer, bool>();
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u64, u64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::GreaterThanOrEqualTo, u64, Integer, bool>();
				break;


			case BinaryExpressionType::Equals:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::Equals, u64, u64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::Equals, u64, Integer, bool>();
				break;

			case BinaryExpressionType::NotEquals:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &binop<BinaryExpressionType::NotEquals, u64, u64, bool>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &binop<BinaryExpressionType::NotEquals, u64, Integer, bool>();
				break;


			default:
				break;
		}

		return nullptr;
	}

	ir::AssignmentOperatorIr* U64TypeContext::getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const
	{
		switch (assignmentType)
		{
			case AssignmentType::Assign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::Assign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::Assign, u64, Integer>();
				break;

			case AssignmentType::AddAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::AddAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::AddAssign, u64, Integer>();
				break;

			case AssignmentType::SubtractAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::SubtractAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::SubtractAssign, u64, Integer>();
				break;

			case AssignmentType::MultiplyAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::MultiplyAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::MultiplyAssign, u64, Integer>();
				break;

			case AssignmentType::DivideAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::DivideAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::DivideAssign, u64, Integer>();
				break;

			case AssignmentType::ModulusAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::ModulusAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::ModulusAssign, u64, Integer>();
				break;

			case AssignmentType::LeftShiftAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::LeftShiftAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::LeftShiftAssign, u64, Integer>();
				break;

			case AssignmentType::RightShiftAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::RightShiftAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::RightShiftAssign, u64, Integer>();
				break;

			case AssignmentType::BitwiseOrAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::BitwiseOrAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseOrAssign, u64, Integer>();
				break;

			case AssignmentType::BitwiseXorAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::BitwiseXorAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseXorAssign, u64, Integer>();
				break;

			case AssignmentType::BitwiseAndAssign:
				if (other == ir::PrimitiveIr::u64Primitive)
					return &assgn<AssignmentType::BitwiseAndAssign, u64>();

				if (other == ir::PrimitiveIr::integerPrimitive)
					return &assgn<AssignmentType::BitwiseAndAssign, u64, Integer>();
				break;
		}
		
		return nullptr;
	}
}
