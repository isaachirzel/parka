#include "parka/ir/BoolPrimitiveIr.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/log/Log.hpp"

namespace parka::ir
{
	BoolPrimitiveIr BoolPrimitiveIr::instance;

	BinaryOperatorIr equalsBinaryOperator(BinaryExpressionType::Equals, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance);
	BinaryOperatorIr notEqualsBinaryOperator(BinaryExpressionType::NotEquals, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance);
	BinaryOperatorIr booleanOrBinaryOperator(BinaryExpressionType::BooleanOr, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance);
	BinaryOperatorIr booleanAndBinaryOperator(BinaryExpressionType::BooleanAnd, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance, BoolPrimitiveIr::instance);

	BoolPrimitiveIr::BoolPrimitiveIr():
		TypeIr(TypeCategory::Bool),
		LValueIr(ResolvableType::Primitive),
		_symbol("bool")
	{}

	ConversionIr* BoolPrimitiveIr::getConversion(const TypeIr&) const
	{
		log::notImplemented(here());
	}

	BinaryOperatorIr* BoolPrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& rhs) const
	{
		if (&rhs != &instance)
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
		out << _symbol;

		return out;
	}
}
