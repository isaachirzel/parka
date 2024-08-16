#ifndef PARKA_AST_EXPRESSION_MEMBER_ACCESS_HPP
#define PARKA_AST_EXPRESSION_MEMBER_ACCESS_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/parser/Token.hpp"
#include "parka/util/Result.hpp"

namespace parka::ast
{
	class MemberAccessExpressionAst: public ExpressionAst
	{
		fs::FileSnippet _snippet;
		ExpressionAst& _expression;
		IdentifierAst _identifier;

	public:

		MemberAccessExpressionAst(ExpressionAst& expression, IdentifierAst&& identifier):
		ExpressionAst(ExpressionType::MemberAccess),
		_snippet(expression.snippet() + identifier.snippet()),
		_expression(expression),
		_identifier(std::move(identifier))
		{}
		MemberAccessExpressionAst(MemberAccessExpressionAst&&) = default;
		MemberAccessExpressionAst(const MemberAccessExpressionAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }

		const auto& expression() const { return _expression; }
		const auto& identifier() const { return _identifier; }
	};
}

#endif
