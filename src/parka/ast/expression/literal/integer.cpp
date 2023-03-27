#include "parka/ast/expression/literal/integer.hpp"
#include "parka/entity/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<u64> parseInteger(Token& token)
{
	// TODO: Handle overflow

	if (token.type() != TokenType::IntegerLiteral)
	{
		printParseError(token, "integer");
		return {};
	}

	u64 value = 0;

	for (usize i = 0; i < token.length(); ++i)
	{
		value *= 10;
		value += token[i] - '0';
	}
	
	return value;
}

usize getMinimumIntegerBits(u64 value)
{
	usize bits = 0;

	while (value > 0)
	{
		value >>= 1;
		bits += 1;
	}

	return bits;
}

Optional<ExpressionId> IntegerLiteral::parse(Token& token)
{
	auto value = parseInteger(token);

	if (!value)
		return {};

	auto bits = getMinimumIntegerBits(value);
	auto literal = IntegerLiteral(token, value.value(), bits);
	auto id = NodeBank::add(std::move(literal));

	token.increment();

	return id;
}
