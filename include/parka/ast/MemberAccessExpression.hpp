#ifndef PARKA_SYNTAX_EXPRESSION_MEMBER_ACCESS_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_MEMBER_ACCESS_SYNTAX_HPP

#include "parka/ast/Expression.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class MemberAccessExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _expression;
		Token _member;

	public:

		MemberAccessExpressionSyntax(ExpressionSyntax& expression, const Token& member);
		MemberAccessExpressionSyntax(MemberAccessExpressionSyntax&&) = default;
		MemberAccessExpressionSyntax(const MemberAccessExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token, ExpressionSyntax& primary);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::MemberAccess; }
		const auto& expression() const { return _expression; }
		const auto& member() const { return _member; }
	};
}

#endif
