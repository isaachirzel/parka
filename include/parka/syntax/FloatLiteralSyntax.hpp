#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_FLOAT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_FLOAT_SYNTAX_HPP

#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class FloatLiteralSyntax : public LiteralSyntax
	{
		Token _token;
		double _value;

		FloatLiteralSyntax(const Token& token, double value) :
		_token(token),
		_value(value)
		{}

	public:

		FloatLiteralSyntax(FloatLiteralSyntax&&) = default;
		FloatLiteralSyntax(const FloatLiteralSyntax&) = delete;
		~FloatLiteralSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);
	};
}

#endif
