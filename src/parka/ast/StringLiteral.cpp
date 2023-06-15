#include "parka/ast/StringLiteral.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	ExpressionSyntax *StringLiteralSyntax::parse(Token& token)
	{
		if (token.type() != TokenType::StringLiteralSyntax)
		{
			log::parseError(token, "string");
			return {};
		}

		auto *syntax = new StringLiteralSyntax(token, token.text());

		token.increment();

		return syntax;
	}

	ExpressionContext *StringLiteralSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
