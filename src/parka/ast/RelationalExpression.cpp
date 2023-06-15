#include "parka/ast/RelationalExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/ShiftExpression.hpp"

namespace parka
{
	static Optional<RelationalType> parseRelationalType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::GreaterThan:
				return RelationalType::GreaterThan;

			case TokenType::LessThan:
				return RelationalType::LessThan;

			case TokenType::GreaterThanOrEqualTo:
				return RelationalType::GreaterThanOrEqualTo;

			case TokenType::LessThanOrEqualTo:
				return RelationalType::LessThanOrEqualTo;

			default:
				return {};
		}
	}
	
	ExpressionSyntax *RelationalExpressionSyntax::parse(Token& token)
	{
		auto *lhs = ShiftExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = parseRelationalType(token);

		while (type)
		{
			token.increment();

			auto rhs = ShiftExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new RelationalExpressionSyntax(*lhs, *rhs, *type);
			type = parseRelationalType(token);
		}

		return lhs;
	}

	ExpressionContext *RelationalExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}