#include "parka/ast/IntegerLiteral.hpp"
#include "parka/ir/IntegerLiteral.hpp"
#include "parka/log/Log.hpp"
#include "parka/ir/ValueType.hpp"

namespace parka::ast
{
	constexpr u64 u8MaxValue =	0x000000FF;
	constexpr u64 u16MaxValue =	0x0000FFFF;
	constexpr u64 u32MaxValue =	0xFFFFFFFF;

	static Optional<u64> getIntegerValue(const Snippet& snippet)
	{
		u64 value = 0;
		const auto length = snippet.length();

		for (usize i = 0; i < length; ++i)
		{
			auto previousValue = value;

			value *= 10;
			value += snippet[i] - '0';

			auto isOverflown = value < previousValue;

			if (isOverflown)
			{
				log::error(snippet, "Integer literal is too large to fit in a 64 bit value.");
				return {};
			} 
		}
		
		return value;
	}

	static const ir::ValueType& getIntegerValueType(u64 value)
	{
		using ir::ValueType;

		if (value > u32MaxValue)
			return ValueType::u64Type;

		if (value > u16MaxValue)
			return ValueType::u32Type;

		if (value > u8MaxValue)
			return ValueType::u16Type;

		return ValueType::u8Type;
	}

	ExpressionAst *IntegerLiteralAst::parse(Token& token)
	{
		if (token.type() != TokenType::IntegerLiteralAst)
		{
			log::parseError(token, "integer");
			return {};
		}

		auto *syntax = new IntegerLiteralAst(token);

		token.increment();

		return syntax;
	}

	ir::ExpressionIr *IntegerLiteralAst::validate(SymbolTable&)
	{
		auto value = getIntegerValue(_snippet);

		if (!value)
			return {};

		const auto& type = getIntegerValueType(*value);

		auto *context = new ir::IntegerLiteralIr(*value, ir::ValueType(type));

		return context;
	}
}
