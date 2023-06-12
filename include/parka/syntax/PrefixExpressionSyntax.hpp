#ifndef PARKA_SYNTAX_EXPRESSION_PREFIX_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_PREFIX_SYNTAX_HPP

#include "parka/enum/PrefixType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

#include "parka/Token.hpp"

namespace parka
{
	class PrefixExpressionSyntax : public ExpressionSyntax
	{
		Token _token;
		ExpressionSyntax& _expression;
		PrefixType _type;

	public:

		PrefixExpressionSyntax(PrefixType type, ExpressionSyntax& expression, const Token& token) :
		_token(token),
		_expression(expression),
		_type(type)
		{}
		PrefixExpressionSyntax(PrefixExpressionSyntax&&) = default;
		PrefixExpressionSyntax(const PrefixExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Prefix; }
		const auto& token() const { return _token; }
		const auto& expression() const { return _expression; }
		const auto& type() const { return _type; }
	};
}

#endif
