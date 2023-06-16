
#ifndef PARKA_AST_EXPRESSION_CONDITIONAL_HPP
#define PARKA_AST_EXPRESSION_CONDITIONAL_HPP

#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class ConditionalExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _condition;
		ExpressionAst& _trueCase;
		ExpressionAst& _falseCase;

	public:

		ConditionalExpressionAst(ExpressionAst& condition, ExpressionAst& trueCase, ExpressionAst& falseCase) :
		_snippet(condition.snippet() + falseCase.snippet()),
		_condition(condition),
		_trueCase(trueCase),
		_falseCase(falseCase)
		{}
		ConditionalExpressionAst(ConditionalExpressionAst&&) = default;
		ConditionalExpressionAst(const ConditionalExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Conditional; }
		const Snippet& snippet() const { return _snippet; }

		const auto& condition() const { return _condition; }
		const auto& trueCase() const { return _trueCase; }
		const auto& falseCase() const { return _falseCase; }
	};
}

#endif
