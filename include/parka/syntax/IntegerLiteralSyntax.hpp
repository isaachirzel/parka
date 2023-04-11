#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_INTEGER_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_INTEGER_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/util/Primitives.hpp"
#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class IntegerLiteralSyntax : public LiteralSyntax
	{
		Token _token;
		u64 _value;
		u32 _bytes;

		IntegerLiteralSyntax(const Token& token, u64 value, u32 bytes) :
		_token(token),
		_value(value),
		_bytes(bytes)
		{}

	public:

		IntegerLiteralSyntax(IntegerLiteralSyntax&&) = default;
		IntegerLiteralSyntax(const IntegerLiteralSyntax&) = delete;
		~IntegerLiteralSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);
	};
}

#endif
