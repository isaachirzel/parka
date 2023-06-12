#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/EqualityExpressionSyntax.hpp"

namespace parka
{
	ExpressionSyntax *BitwiseAndExpressionSyntax::parse(Token& token)
	{
		auto *lhs = EqualityExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Ampersand)
		{
			token.increment();

			auto rhs = EqualityExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BitwiseAndExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}

	ExpressionContext *BitwiseAndExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
