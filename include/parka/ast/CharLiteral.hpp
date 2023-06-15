#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_CHAR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_CHAR_SYNTAX_HPP

#include "parka/ast/Literal.hpp"

namespace parka
{
	class CharLiteralSyntax : public ExpressionSyntax
	{
		Token _token;
		char _value;
		// TODO: UTF-8

	public:

		CharLiteralSyntax(const Token& token, char value) :
		_token(token),
		_value(value)
		{}
		CharLiteralSyntax(CharLiteralSyntax&&) = default;
		CharLiteralSyntax(const CharLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::CharLiteral; }
		const auto& token() const { return _token; }
		const auto& value() const { return _value; }
	};
}

#endif
