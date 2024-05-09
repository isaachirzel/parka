#ifndef PARKA_AST_PREFIX_EXPRESSION_HPP
#define PARKA_AST_PREFIX_EXPRESSION_HPP

#include "parka/enum/PrefixType.hpp"
#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class PrefixExpressionAst: public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _expression;
		PrefixType _type;

	public:

		PrefixExpressionAst(const Snippet& snippet, PrefixType type, ExpressionAst& expression):
		ExpressionAst(ExpressionType::Prefix),
		_snippet(snippet),
		_expression(expression),
		_type(type)
		{}
		PrefixExpressionAst(PrefixExpressionAst&&) = default;
		PrefixExpressionAst(const PrefixExpressionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& expression() const { return _expression; }
		const auto& type() const { return _type; }
	};
}

#endif
