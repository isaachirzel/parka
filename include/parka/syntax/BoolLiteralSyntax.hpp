#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_BOOL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_BOOL_SYNTAX_HPP

#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class BoolLiteralSyntax : public ExpressionSyntax
	{
		Token _token;
		bool _value;

	public:

		BoolLiteralSyntax(const Token& token, bool value) :
		_token(token),
		_value(value)
		{}
		BoolLiteralSyntax(BoolLiteralSyntax&&) = default;
		BoolLiteralSyntax(const BoolLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::BoolLiteral; }
		const auto& token() const { return _token; }
		const auto& value() const { return _value; }
	};
}

#endif
