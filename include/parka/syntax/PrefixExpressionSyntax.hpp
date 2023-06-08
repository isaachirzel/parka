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
		const ExpressionSyntax& _expression;
		PrefixType _type;

		PrefixExpressionSyntax(PrefixType type, const ExpressionSyntax& expression, const Token& token) :
		_token(token),
		_expression(expression),
		_type(type)
		{}

	public:

		PrefixExpressionSyntax(PrefixExpressionSyntax&&) = default;
		PrefixExpressionSyntax(const PrefixExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::Prefix; }
		const auto& token() const { return _token; }
		const auto& expression() const { return _expression; }
		const auto& type() const { return _type; }
	};
}

#endif
