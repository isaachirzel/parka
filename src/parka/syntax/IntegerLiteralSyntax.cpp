#include "parka/syntax/IntegerLiteralSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/type/ValueType.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<u64> parseInteger(Token& token)
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

	const ExpressionSyntax *IntegerLiteralSyntax::parse(Token& token)
	{
		auto value = parseInteger(token);

		if (!value)
			return {};

		auto bits = getMinimumIntegerBytes(value);
		auto literal = IntegerLiteralSyntax(token, *value, bits);
		auto& syntax = ExpressionSyntax::create(std::move(literal));

		token.increment();

		return &syntax;
	}

	// bool IntegerLiteralSyntax::validate(const EntitySyntax&)
	// {
	// 	return true;
	// }

	// Optional<ValueType> IntegerLiteralSyntax::getType() const
	// {
	// 	switch (_bytes)
	// 	{
	// 		case 0:
	// 		case 1:
	// 			return ValueType::i8Type;
	// 		case 2:
	// 			return ValueType::i16Type;
	// 		case 3:
	// 		case 4:
	// 			return ValueType::i32Type;
	// 		case 5:
	// 		case 6:
	// 		case 7:
	// 		case 8:
	// 			return ValueType::i64Type;

	// 		default:
	// 			log::fatal("Unable to get ValueType of IntegerLiteralSyntax with size: $", _bytes);
	// 	}
	// }
}
