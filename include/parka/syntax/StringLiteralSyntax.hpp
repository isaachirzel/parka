#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_STRING_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_STRING_SYNTAX_HPP

#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class StringLiteralSyntax : public ExpressionSyntax
	{
		Token _token;
		String _value;

	public:

		StringLiteralSyntax(Token token, String&& value) :
		_token(token),
		_value(std::move(value))
		{}
		StringLiteralSyntax(StringLiteralSyntax&&) = default;
		StringLiteralSyntax(const StringLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		
		ExpressionType expressionType() const { return ExpressionType::StringLiteral; }
	};
}

#endif
