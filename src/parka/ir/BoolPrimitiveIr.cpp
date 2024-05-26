#include "parka/ir/BoolPrimitiveIr.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/log/Log.hpp"

namespace parka::ir
{
	BoolPrimitiveIr BoolPrimitiveIr::boolPrimitive("bool");

	BinaryOperatorIr equalsBinaryOperator(BinaryExpressionType::Equals, BoolPrimitiveIr::boolPrimitive, BoolPrimitiveIr::boolPrimitive, BoolPrimitiveIr::boolPrimitive);
	BinaryOperatorIr notEqualsBinaryOperator(BinaryExpressionType::NotEquals, BoolPrimitiveIr::boolPrimitive, BoolPrimitiveIr::boolPrimitive, BoolPrimitiveIr::boolPrimitive);
	BinaryOperatorIr booleanOrBinaryOperator(BinaryExpressionType::BooleanOr, BoolPrimitiveIr::boolPrimitive, BoolPrimitiveIr::boolPrimitive, BoolPrimitiveIr::boolPrimitive);
	BinaryOperatorIr booleanAndBinaryOperator(BinaryExpressionType::BooleanAnd, BoolPrimitiveIr::boolPrimitive, BoolPrimitiveIr::boolPrimitive, BoolPrimitiveIr::boolPrimitive);

	BoolPrimitiveIr::BoolPrimitiveIr(const char *name):
		TypeIr(TypeCategory::Bool),
		LValueIr(ResolvableType::Primitive),
		_name(name)
	{}

	ConversionIr* BoolPrimitiveIr::getConversion(const TypeIr&) const
	{
		log::notImplemented(here());
	}

	BinaryOperatorIr* BoolPrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& rhs) const
	{
		if (&rhs != &boolPrimitive)
			return nullptr;

		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Equals:
				return &equalsBinaryOperator;

			case BinaryExpressionType::NotEquals:
				return &notEqualsBinaryOperator;

			case BinaryExpressionType::BooleanOr:
				return &booleanOrBinaryOperator;

			case BinaryExpressionType::BooleanAnd:
				return &booleanAndBinaryOperator;

			default:
				break;
		}

		return nullptr;
	}

	std::ostream& BoolPrimitiveIr::printType(std::ostream& out) const
	{
		out << _name;

		return out;
	}
}
