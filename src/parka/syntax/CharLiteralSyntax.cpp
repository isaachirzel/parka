#include "parka/syntax/CharLiteralSyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<char> parseChar(Token& token)
	{
		if (token.type() != TokenType::CharacterLiteral)
		{
			printParseError(token, "character");
			return {};
		}

		if (token.length() != 3)
		{
			printError(token, "character literals may only contain 1 character", NULL);
			return {};
		}

		auto character = token[0];

		return character;
	}

	Optional<ExpressionId> CharLiteralSyntax::parse(Token& token)
	{
		auto value = parseChar(token);

		if (!value)
			return {};

		auto expression = CharLiteralSyntax(token, *value);
		auto id = Storage::add(std::move(expression));

		token.increment();

		return id;
	}
}
