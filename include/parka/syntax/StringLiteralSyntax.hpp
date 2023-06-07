#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_STRING_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_STRING_SYNTAX_HPP

#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class StringLiteralSyntax : public LiteralSyntax
	{
		Token _token;
		String _value;

		StringLiteralSyntax(Token token, String&& value) :
		_token(token),
		_value(std::move(value))
		{}

	public:

		StringLiteralSyntax(StringLiteralSyntax&&) = default;
		StringLiteralSyntax(const StringLiteralSyntax&) = delete;

		static Optional<ExpressionSyntaxId> parse(Token& token);
	};
}

#endif
