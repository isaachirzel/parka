#include "parka/ast/BooleanOrExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/BooleanAndExpression.hpp"

namespace parka
{
	ExpressionSyntax *BooleanOrExpressionSyntax::parse(Token& token)
	{
		auto *lhs = BooleanAndExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanOr)
		{
			token.increment();

			auto rhs = BooleanAndExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BooleanOrExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}

	ExpressionContext *BooleanOrExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}