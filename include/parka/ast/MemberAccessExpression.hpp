#ifndef PARKA_AST_EXPRESSION_MEMBER_ACCESS_HPP
#define PARKA_AST_EXPRESSION_MEMBER_ACCESS_HPP

#include "parka/ast/Expression.hpp"
#include "parka/parser/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ast
{
	class MemberAccessExpressionAst: public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _expression;
		Identifier _identifier;

	public:

		MemberAccessExpressionAst(ExpressionAst& expression, Identifier&& identifier):
		ExpressionAst(ExpressionType::MemberAccess),
		_snippet(expression.snippet() + identifier.snippet()),
		_expression(expression),
		_identifier(std::move(identifier))
		{}
		MemberAccessExpressionAst(MemberAccessExpressionAst&&) = default;
		MemberAccessExpressionAst(const MemberAccessExpressionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }

		const auto& expression() const { return _expression; }
		const auto& identifier() const { return _identifier; }
	};
}

#endif
