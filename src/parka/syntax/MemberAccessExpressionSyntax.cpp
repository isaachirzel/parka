#include "parka/syntax/MemberAccessExpressionSyntax.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	MemberAccessExpressionSyntax::MemberAccessExpressionSyntax(ExpressionSyntax& expression, const Token& member) :
	_expression(expression),
	_member(member)
	{}

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

		auto *syntax = new MemberAccessExpressionSyntax(primary, token);

		token.increment();

		return syntax;
	}

	ExpressionContext *MemberAccessExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
