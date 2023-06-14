#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_FLOAT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_FLOAT_SYNTAX_HPP

#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class FloatLiteralSyntax : public ExpressionSyntax
	{
		Token _token;
		double _value;

	public:

		FloatLiteralSyntax(const Token& token, double value) :
		_token(token),
		_value(value)
		{}
		FloatLiteralSyntax(FloatLiteralSyntax&&) = default;
		FloatLiteralSyntax(const FloatLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		// TODO: Actually determine size of float
		const ValueType& valueType() const { return ValueType::f64Type; }
		ExpressionType expressionType() const { return ExpressionType::FloatLiteral; }
	};
}

#endif
