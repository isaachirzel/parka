#include "parka/validation/IntegerTypeContext.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	IntegerTypeContext IntegerTypeContext::instance;

	ir::ConversionIr* IntegerTypeContext::getConversionTo(const ir::TypeIr& toType) const
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

	ir::BinaryOperatorIr* IntegerTypeContext::getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const
	{
		return nullptr;
	}
	
	ir::AssignmentOperatorIr* IntegerTypeContext::getAssignmentOperator(AssignmentType, const ir::TypeIr&) const
	{
		return nullptr;
	}
}
