#ifndef PARKA_SYNTAX_EXPRESSION_MEMBER_ACCESS_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_MEMBER_ACCESS_SYNTAX_HPP

#include "parka/ast/Expression.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class MemberAccessExpressionSyntax : public ExpressionSyntax
	{
		Snippet _snippet;
		ExpressionSyntax& _expression;
		Identifier _identifier;

	public:

		MemberAccessExpressionSyntax(ExpressionSyntax& expression, Identifier&& identifier) :
		_snippet(expression.snippet() + identifier.snippet()),
		_expression(expression),
		_identifier(std::move(identifier))
		{}
		MemberAccessExpressionSyntax(MemberAccessExpressionSyntax&&) = default;
		MemberAccessExpressionSyntax(const MemberAccessExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token, ExpressionSyntax& primary);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::MemberAccess; }
		const Snippet& snippet() const { return _snippet; }

		const auto& expression() const { return _expression; }
		const auto& identifier() const { return _identifier; }
	};
}

#endif
