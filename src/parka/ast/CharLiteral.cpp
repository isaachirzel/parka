#include "parka/ast/CharLiteral.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	static Optional<char> parseChar(Token& token)
	{
		if (token.type() != TokenType::CharacterLiteral)
		{
			log::parseError(token, "character");
			return {};
		}

		if (token.length() != 3)
		{
			log::error(token, "character literals may only contain 1 character", nullptr);
			return {};
		}

		auto character = token[0];

		return character;
	}

	ExpressionSyntax *CharLiteralSyntax::parse(Token& token)
	{
		auto value = parseChar(token);

		if (!value)
			return {};

		auto *syntax = new CharLiteralSyntax(token, *value);

		token.increment();

		return syntax;
	}

	ExpressionContext *CharLiteralSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
