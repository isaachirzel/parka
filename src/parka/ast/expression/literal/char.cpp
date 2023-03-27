#include "parka/ast/expression/literal/char.hpp"
#include "parka/entity/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<char> parseChar(Token& token)
{
	if (token.type() != TokenType::CharacterLiteral)
	{
		printParseError(token, "character");
		return {};
	}

	if (token.length() != 3)
	{
		printTokenError(token, "character literals may only contain 1 character", NULL);
		return {};
	}

	auto character = token[0];

	return character;
}

Optional<ExpressionId> CharLiteral::parse(Token& token)
{
	auto value = parseChar(token);

	if (!value)
		return {};

	auto expression = CharLiteral(token, value.value());
	auto id = NodeBank::add(std::move(expression));

	token.increment();

	return id;
}
