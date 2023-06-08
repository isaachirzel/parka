#include "parka/syntax/CharLiteralSyntax.hpp"

#include "parka/log/Log.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<char> parseChar(Token& token)
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

	const ExpressionSyntax *CharLiteralSyntax::parse(Token& token)
	{
		auto value = parseChar(token);

		if (!value)
			return {};

		auto expression = CharLiteralSyntax(token, *value);
		auto& syntax = ExpressionSyntax::create(std::move(expression));

		token.increment();

		return &syntax;
	}
}
