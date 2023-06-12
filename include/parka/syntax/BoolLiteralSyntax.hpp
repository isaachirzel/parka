#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_BOOL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_BOOL_SYNTAX_HPP

#include "parka/context/BoolLiteralContext.hpp"
#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class BoolLiteralSyntax : public ExpressionSyntax
	{
		Token _token;
		bool _value;

	public:

		BoolLiteralSyntax(const Token& token, bool value);
		BoolLiteralSyntax(BoolLiteralSyntax&&) = default;
		BoolLiteralSyntax(const BoolLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::BoolLiteral; }
		const auto& token() const { return _token; }
		const auto& value() const { return _value; }
	};
}

#endif
