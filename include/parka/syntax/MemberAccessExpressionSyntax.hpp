#ifndef PARKA_SYNTAX_EXPRESSION_MEMBER_ACCESS_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_MEMBER_ACCESS_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class MemberAccessExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _expression;
		Token _member;

		MemberAccessExpressionSyntax(ExpressionId&& expression, const Token& member) :
		_expression(std::move(expression)),
		_member(member)
		{}

	public:

		static Optional<ExpressionId> parse(Token& token, ExpressionId primary);

		const auto& expression() const { return _expression; }
		const auto& member() const { return _member; }
	};
}

#endif
