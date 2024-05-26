
#ifndef PARKA_AST_EXPRESSION_CONDITIONAL_HPP
#define PARKA_AST_EXPRESSION_CONDITIONAL_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/enum/ExpressionType.hpp"

namespace parka::ast
{
	class ConditionalExpressionAst: public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _condition;
		ExpressionAst& _thenCase;
		ExpressionAst& _elseCase;

	public:

		ConditionalExpressionAst(const Snippet& snippet, ExpressionAst& condition, ExpressionAst& thenCase, ExpressionAst& elseCase):
			ExpressionAst(ExpressionType::Conditional),
			_snippet(snippet),
			_condition(condition),
			_thenCase(thenCase),
			_elseCase(elseCase)
		{}
		ConditionalExpressionAst(ConditionalExpressionAst&&) = default;
		ConditionalExpressionAst(const ConditionalExpressionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& condition() const { return _condition; }
		const auto& thenCase() const { return _thenCase; }
		const auto& elseCase() const { return _elseCase; }
	};
}

#endif
