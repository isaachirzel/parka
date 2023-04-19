#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_CHAR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_CHAR_SYNTAX_HPP

#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class CharLiteralSyntax : public LiteralSyntax
	{
		Token _token;
		char _value;
		// TODO: UTF-8

		CharLiteralSyntax(const Token& token, char value) :
		_token(token),
		_value(value)
		{}

	public:

		CharLiteralSyntax(CharLiteralSyntax&&) = default;
		CharLiteralSyntax(const CharLiteralSyntax&) = delete;

		static Optional<ExpressionSyntaxId> parse(Token& token);
	};
}

#endif
