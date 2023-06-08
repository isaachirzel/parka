#ifndef PARKA_SYNTAX_EXPRESSION_MEMBER_ACCESS_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_MEMBER_ACCESS_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class MemberAccessExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _expression;
		Token _member;

		MemberAccessExpressionSyntax(const ExpressionSyntax& expression, const Token& member) :
		_expression(expression),
		_member(member)
		{}

	public:

		static const ExpressionSyntax *parse(Token& token, const ExpressionSyntax& primary);

		ExpressionType expressionType() const { return ExpressionType::MemberAccess; }
		const auto& expression() const { return _expression; }
		const auto& member() const { return _member; }
	};
}

#endif
