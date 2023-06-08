
#ifndef PARKA_SYNTAX_EXPRESSION_CONDITIONAL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CONDITIONAL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class ConditionalExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _condition;
		const ExpressionSyntax& _trueCase;
		const ExpressionSyntax& _falseCase;

		ConditionalExpressionSyntax(const ExpressionSyntax& condition, const ExpressionSyntax& trueCase, const ExpressionSyntax& falseCase) :
		_condition(condition),
		_trueCase(trueCase),
		_falseCase(falseCase)
		{}

	public:

		ConditionalExpressionSyntax(ConditionalExpressionSyntax&&) = default;
		ConditionalExpressionSyntax(const ConditionalExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::Conditional; }
		const auto& condition() const { return _condition; }
		const auto& trueCase() const { return _trueCase; }
		const auto& falseCase() const { return _falseCase; }
	};
}

#endif
