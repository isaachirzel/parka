#include "parka/validation/IntegerTypeContext.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/PrimitiveType.hpp"
#include "parka/enum/TypeCategory.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	IntegerTypeContext IntegerTypeContext::instance;

	ir::CastIr* IntegerTypeContext::getImplicitCastTo(const ir::TypeIr& toType) const
	{
		if (toType.typeCategory != TypeCategory::Primitive)
			return nullptr;

		const auto& primitive = static_cast<const ir::PrimitiveIr&>(toType);

		switch (primitive.primitiveType())
		{
			case PrimitiveType::I8:
				return &conv<Integer, i8>();

			case PrimitiveType::I16:
				return &conv<Integer, i16>();

			case PrimitiveType::I32:
				return &conv<Integer, i32>();

			case PrimitiveType::I64:
				return &conv<Integer, i64>();

			case PrimitiveType::U8:
				return &conv<Integer, u8>();

			case PrimitiveType::U16:
				return &conv<Integer, u16>();

			case PrimitiveType::U32:
				return &conv<Integer, u32>();

			case PrimitiveType::U64:
				return &conv<Integer, u64>();

			default:
				break;
		}

		return nullptr;
	}

	ir::CastIr* IntegerTypeContext::getExplicitCastTo(const ir::TypeIr& toType) const
	{
		return getImplicitCastTo(toType);
	}

	ir::BinaryOperatorIr* IntegerTypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const
	{
		if (other.typeCategory != TypeCategory::Primitive)
			return nullptr;

		const auto& primitive = static_cast<const ir::PrimitiveIr&>(other);

		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::Add, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::Add, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::Add, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::Add, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::Add, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::Add, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::Add, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::Add, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::Add, Integer, u64, u64>();

					default:
						break;
			}
				break;

			case BinaryExpressionType::Subtract:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::Subtract, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::Subtract, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::Subtract, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::Subtract, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::Subtract, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::Subtract, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::Subtract, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::Subtract, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::Subtract, Integer, u64, u64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::Multiply:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::Multiply, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::Multiply, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::Multiply, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::Multiply, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::Multiply, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::Multiply, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::Multiply, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::Multiply, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::Multiply, Integer, u64, u64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::Divide:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::Divide, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::Divide, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::Divide, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::Divide, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::Divide, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::Divide, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::Divide, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::Divide, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::Divide, Integer, u64, u64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::Modulus:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::Modulus, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::Modulus, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::Modulus, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::Modulus, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::Modulus, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::Modulus, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::Modulus, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::Modulus, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::Modulus, Integer, u64, u64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::BitwiseOr:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::BitwiseOr, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::BitwiseOr, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::BitwiseOr, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::BitwiseOr, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::BitwiseOr, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::BitwiseOr, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::BitwiseOr, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::BitwiseOr, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::BitwiseOr, Integer, u64, u64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::BitwiseXor:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::BitwiseXor, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::BitwiseXor, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::BitwiseXor, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::BitwiseXor, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::BitwiseXor, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::BitwiseXor, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::BitwiseXor, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::BitwiseXor, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::BitwiseXor, Integer, u64, u64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::BitwiseAnd:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::BitwiseAnd, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::BitwiseAnd, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::BitwiseAnd, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::BitwiseAnd, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::BitwiseAnd, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::BitwiseAnd, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::BitwiseAnd, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::BitwiseAnd, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::BitwiseAnd, Integer, u64, u64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::LeftShift:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::LeftShift, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::LeftShift, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::LeftShift, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::LeftShift, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::LeftShift, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::LeftShift, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::LeftShift, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::LeftShift, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::LeftShift, Integer, u64, u64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::RightShift:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::RightShift, Integer, Integer, Integer>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::RightShift, Integer, i8, i8>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::RightShift, Integer, i16, i16>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::RightShift, Integer, i32, i32>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::RightShift, Integer, i64, i64>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::RightShift, Integer, u8, u8>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::RightShift, Integer, u16, u16>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::RightShift, Integer, u32, u32>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::RightShift, Integer, u64, u64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::LessThan:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::LessThan, Integer, Integer, bool>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::LessThan, Integer, i8, bool>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::LessThan, Integer, i16, bool>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::LessThan, Integer, i32, bool>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::LessThan, Integer, i64, bool>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::LessThan, Integer, u8, bool>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::LessThan, Integer, u16, bool>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::LessThan, Integer, u32, bool>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::LessThan, Integer, u64, bool>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::GreaterThan:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::GreaterThan, Integer, Integer, bool>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::GreaterThan, Integer, i8, bool>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::GreaterThan, Integer, i16, bool>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::GreaterThan, Integer, i32, bool>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::GreaterThan, Integer, i64, bool>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::GreaterThan, Integer, u8, bool>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::GreaterThan, Integer, u16, bool>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::GreaterThan, Integer, u32, bool>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::GreaterThan, Integer, u64, bool>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Integer, Integer, bool>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Integer, i8, bool>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Integer, i16, bool>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Integer, i32, bool>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Integer, i64, bool>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Integer, u8, bool>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Integer, u16, bool>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Integer, u32, bool>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Integer, u64, bool>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Integer, Integer, bool>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Integer, i8, bool>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Integer, i16, bool>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Integer, i32, bool>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Integer, i64, bool>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Integer, u8, bool>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Integer, u16, bool>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Integer, u32, bool>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Integer, u64, bool>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::Equals:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::Equals, Integer, Integer, bool>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::Equals, Integer, i8, bool>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::Equals, Integer, i16, bool>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::Equals, Integer, i32, bool>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::Equals, Integer, i64, bool>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::Equals, Integer, u8, bool>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::Equals, Integer, u16, bool>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::Equals, Integer, u32, bool>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::Equals, Integer, u64, bool>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::NotEquals:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Integer:
						return &binop<BinaryExpressionType::NotEquals, Integer, Integer, bool>();

					case PrimitiveType::I8:
						return &binop<BinaryExpressionType::NotEquals, Integer, i8, bool>();

					case PrimitiveType::I16:
						return &binop<BinaryExpressionType::NotEquals, Integer, i16, bool>();

					case PrimitiveType::I32:
						return &binop<BinaryExpressionType::NotEquals, Integer, i32, bool>();

					case PrimitiveType::I64:
						return &binop<BinaryExpressionType::NotEquals, Integer, i64, bool>();

					case PrimitiveType::U8:
						return &binop<BinaryExpressionType::NotEquals, Integer, u8, bool>();

					case PrimitiveType::U16:
						return &binop<BinaryExpressionType::NotEquals, Integer, u16, bool>();

					case PrimitiveType::U32:
						return &binop<BinaryExpressionType::NotEquals, Integer, u32, bool>();

					case PrimitiveType::U64:
						return &binop<BinaryExpressionType::NotEquals, Integer, u64, bool>();

					default:
						break;
				}
				break;

			default:
				break;
		}

		return nullptr;
	}
	
	ir::AssignmentOperatorIr* IntegerTypeContext::getAssignmentOperator(AssignmentType, const ir::TypeIr&) const
	{
		return nullptr;
	}
}
