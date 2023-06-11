#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"

namespace parka
{
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
}
