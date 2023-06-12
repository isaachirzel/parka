
#ifndef PARKA_SYNTAX_EXPRESSION_CONDITIONAL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CONDITIONAL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class ConditionalExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _condition;
		ExpressionSyntax& _trueCase;
		ExpressionSyntax& _falseCase;

	public:

		ConditionalExpressionSyntax(ExpressionSyntax& condition, ExpressionSyntax& trueCase, ExpressionSyntax& falseCase) :
		_condition(condition),
		_trueCase(trueCase),
		_falseCase(falseCase)
		{}
		ConditionalExpressionSyntax(ConditionalExpressionSyntax&&) = default;
		ConditionalExpressionSyntax(const ConditionalExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Conditional; }
		const auto& condition() const { return _condition; }
		const auto& trueCase() const { return _trueCase; }
		const auto& falseCase() const { return _falseCase; }
	};
}

#endif
