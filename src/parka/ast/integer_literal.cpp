#include "parka/ast/integer_literal.hpp"
#include "parka/type/type.hpp"
#include "parka/node/node_bank.hpp"
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

usize getMinimumIntegerBytes(u64 value)
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

	auto bits = getMinimumIntegerBytes(value);
	auto literal = IntegerLiteral(token, *value, bits);
	auto id = NodeBank::add(std::move(literal));

	token.increment();

	return id;
}

bool IntegerLiteral::validate(const EntityId&)
{
	return true;
}

Optional<Type> IntegerLiteral::getType() const
{
	switch (_bytes)
	{
		case 0:
		case 1:
			return Type::i8Type;
		case 2:
			return Type::i16Type;
		case 3:
		case 4:
			return Type::i32Type;
		case 5:
		case 6:
		case 7:
		case 8:
			return Type::i64Type;

		default:
			exitWithError("Unable to get Type of IntegerLiteral with size: $", _bytes);
	}
}
