#include "parka/ast/IntegerLiteral.hpp"
#include "parka/log/Log.hpp"
#include "parka/type/ValueType.hpp"

namespace parka
{
	constexpr u64 u8MaxValue =	0x000000FF;
	constexpr u64 u16MaxValue =	0x0000FFFF;
	constexpr u64 u32MaxValue =	0xFFFFFFFF;

	IntegerLiteralSyntax::IntegerLiteralSyntax(const Token& token) :
	_token(token)
	{}

	IntegerLiteralContext::IntegerLiteralContext(u64 value, ValueType&& valueType) :
	_value(value),
	_valueType(std::move(valueType))
	{}

	static Optional<u64> getIntegerValue(const Token& token)
	{
		assert(token.type() == TokenType::IntegerLiteralSyntax);

		u64 value = 0;

		for (usize i = 0; i < token.length(); ++i)
		{
			auto previousValue = value;

			value *= 10;
			value += token[i] - '0';

			auto isOverflown = value < previousValue;

			if (isOverflown)
			{
				log::error(token, "Integer literal is too large to fit in a 64 bit value.");
				return {};
			} 
		}
		
		return value;
	}

	static const ValueType& getIntegerValueType(u64 value)
	{
		if (value > u32MaxValue)
			return ValueType::u64Type;

		if (value > u16MaxValue)
			return ValueType::u32Type;

		if (value > u8MaxValue)
			return ValueType::u16Type;

		return ValueType::u8Type;
	}

	ExpressionSyntax *IntegerLiteralSyntax::parse(Token& token)
	{
		if (token.type() != TokenType::IntegerLiteralSyntax)
		{
			log::parseError(token, "integer");
			return {};
		}

		auto *syntax = new IntegerLiteralSyntax(token);

		token.increment();

		return syntax;
	}

	ExpressionContext *IntegerLiteralSyntax::validate(SymbolTable& symbolTable)
	{
		auto value = getIntegerValue(_token);

		if (!value)
			return {};

		const auto& type = getIntegerValueType(*value);

		auto *context = new IntegerLiteralContext(*value, ValueType(type));

		return context;
	}
}
