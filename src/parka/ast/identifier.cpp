#include "parka/ast/identifier.hpp"
#include "parka/token.hpp"
#include "parka/util/print.hpp"

Optional<Identifier> Identifier::parse(Token& token)
{
	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "identifier");
		return {};
	}

	auto identifier = Identifier(token);

	token.increment();

	return identifier;
}
