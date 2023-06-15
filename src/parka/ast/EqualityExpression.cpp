#include "parka/ast/EqualityExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/RelationalExpression.hpp"

namespace parka
{
	static Optional<EqualityType> getEqualityType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Equals:
				return EqualityType::Equals;

			case TokenType::NotEquals:
				return EqualityType::NotEquals;

			default:
				return {};
		}
	}

	ExpressionSyntax *EqualityExpressionSyntax::parse(Token& token)
	{
		auto *lhs = RelationalExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = getEqualityType(token);

		while (type)
		{
			token.increment();

			auto rhs = RelationalExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new EqualityExpressionSyntax(*lhs, *rhs, *type);
			type = getEqualityType(token);
		}

		return lhs;
	}

	ExpressionContext *EqualityExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}