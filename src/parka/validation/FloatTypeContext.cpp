#include "parka/validation/FloatTypeContext.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/util/Float.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	FloatTypeContext FloatTypeContext::instance;

	ir::CastIr* FloatTypeContext::getImplicitCastTo(const ir::TypeIr& toType) const
	{
		if (toType.typeCategory != TypeCategory::Primitive)
			return nullptr;

		const auto& primitive = static_cast<const ir::PrimitiveIr&>(toType);

		switch (primitive.primitiveType())
		{
			case PrimitiveType::F32:
				return &conv<Float, u32>();

			case PrimitiveType::F64:
				return &conv<Float, u64>();

			default:
				break;
		}

		return nullptr;
	}

	ir::CastIr* FloatTypeContext::getExplicitCastTo(const ir::TypeIr& toType) const
	{
		return getImplicitCastTo(toType);
	}

	ir::BinaryOperatorIr* FloatTypeContext::getBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& other) const
	{
		if (other.typeCategory != TypeCategory::Primitive)
			return nullptr;

		const auto& primitive = static_cast<const ir::PrimitiveIr&>(other);

		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::Add, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::Add, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::Add, Float, f64, f64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::Subtract:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::Subtract, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::Subtract, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::Subtract, Float, f64, f64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::Multiply:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::Multiply, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::Multiply, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::Multiply, Float, f64, f64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::Divide:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::Divide, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::Divide, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::Divide, Float, f64, f64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::LessThan:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::LessThan, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::LessThan, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::LessThan, Float, f64, f64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::GreaterThan:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::GreaterThan, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::GreaterThan, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::GreaterThan, Float, f64, f64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::LessThanOrEqualTo, Float, f64, f64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::GreaterThanOrEqualTo, Float, f64, f64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::Equals:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::Equals, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::Equals, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::Equals, Float, f64, f64>();

					default:
						break;
				}
				break;

			case BinaryExpressionType::NotEquals:
				switch (primitive.primitiveType())
				{
					case PrimitiveType::Float:
						return &binop<BinaryExpressionType::NotEquals, Float, Float, Float>();

					case PrimitiveType::F32:
						return &binop<BinaryExpressionType::NotEquals, Float, f32, f32>();

					case PrimitiveType::F64:
						return &binop<BinaryExpressionType::NotEquals, Float, f64, f64>();

					default:
						break;
				}
				break;

			default:
				break;
		}

		return nullptr;
	}

	ir::AssignmentOperatorIr* FloatTypeContext::getAssignmentOperator(AssignmentType assignmentType, const ir::TypeIr& other) const
	{
		return nullptr;
	}
}
