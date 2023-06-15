#include "parka/ast/AdditiveExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/MultiplicativeExpression.hpp"

namespace parka
{
	AdditiveExpressionSyntax::AdditiveExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, AdditiveType type) :
	_lhs(lhs),
	_rhs(rhs),
	_type(type)
	{}

	AdditiveExpressionContext::AdditiveExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AdditiveType additiveType, ValueType&& valueType) :
	_lhs(lhs),
	_rhs(rhs),
	_additiveType(additiveType),
	_valueType(std::move(valueType))
	{}

	static Optional<AdditiveType> getAdditiveType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Plus:
				return AdditiveType::Add;

			case TokenType::Minus:
				return AdditiveType::Subtract;

			default:
				break;
		}

		return {};
	}

	ExpressionSyntax *AdditiveExpressionSyntax::parse(Token& token)
	{
		auto *lhs = MultiplicativeExpressionSyntax::parse(token);

		if (!lhs)
			return {};
		
		auto type = getAdditiveType(token);

		while (type)
		{
			token.increment();

			auto rhs = MultiplicativeExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new AdditiveExpressionSyntax(*lhs, *rhs, *type);;
			type = getAdditiveType(token);
		}

		return lhs;
	}

	ExpressionContext *AdditiveExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		auto *lhs = _lhs.validate(symbolTable);
		auto *rhs = _rhs.validate(symbolTable);

		// TODO: Operators

		if (!lhs || !rhs)
			return nullptr;

		const auto& lhsType = lhs->valueType();
		const auto& rhsType = rhs->valueType();

		if (!rhsType.canConvertTo(lhsType))
		{
			log::error("$ cannot be added to $.", rhsType, lhsType);
			return nullptr;
		}
		log::notImplemented(here());
	}
}
