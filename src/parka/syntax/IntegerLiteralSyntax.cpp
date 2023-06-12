#include "parka/syntax/IntegerLiteralSyntax.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	IntegerLiteralSyntax::IntegerLiteralSyntax(const Token& token, u64 value, u32 bytes) :
	_token(token),
	_value(value),
	_bytes(bytes)
	{}

	static Optional<u64> parseInteger(Token& token)
	{
		// TODO: Handle overflow

		if (token.type() != TokenType::IntegerLiteralSyntax)
		{
			log::parseError(token, "integer");
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

	static usize getMinimumIntegerBytes(u64 value)
	{
		usize bits = 0;

		while (value > 0)
		{
			value >>= 1;
			bits += 1;
		}

		return bits;
	}

	ExpressionSyntax *IntegerLiteralSyntax::parse(Token& token)
	{
		auto value = parseInteger(token);

		if (!value)
			return {};

		auto bits = getMinimumIntegerBytes(value);
		auto *syntax = new IntegerLiteralSyntax(token, *value, bits);

		token.increment();

		return syntax;
	}

	ExpressionContext *IntegerLiteralSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
