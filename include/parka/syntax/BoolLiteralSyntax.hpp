#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_BOOL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_BOOL_SYNTAX_HPP

#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class BoolLiteralSyntax : public LiteralSyntax
	{
		Token _token;
		bool _value;

		BoolLiteralSyntax(const Token& token, bool value) :
		_token(token),
		_value(value)
		{}

	public:

		BoolLiteralSyntax(BoolLiteralSyntax&&) = default;
		BoolLiteralSyntax(const BoolLiteralSyntax&) = delete;
		~BoolLiteralSyntax() = default;

		static Optional<ExpressionSyntaxId> parse(Token& token);
	};
}

#endif
