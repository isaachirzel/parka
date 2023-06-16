#include "parka/ast/MemberAccessExpression.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	ExpressionSyntax *MemberAccessExpressionSyntax::parse(Token& token, ExpressionSyntax& primary)
	{
		if (token.type() != TokenType::Dot)
		{
			log::parseError(token, "'.'");
			return {};
		}

		token.increment();
		
		if (token.type() != TokenType::Identifier)
		{
			log::parseError(token, "member, method, or property name");
			return {};
		}
		
		auto *syntax = new MemberAccessExpressionSyntax(primary, Identifier(token));

		token.increment();

		return syntax;
	}

	ExpressionContext *MemberAccessExpressionSyntax::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
