
#ifndef PARKA_SYNTAX_EXPRESSION_CONDITIONAL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CONDITIONAL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class ConditionalExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _condition;
		ExpressionSyntaxId _trueCase;
		ExpressionSyntaxId _falseCase;

		ConditionalExpressionSyntax(ExpressionSyntaxId&& condition, ExpressionSyntaxId&& trueCase, ExpressionSyntaxId&& falseCase) :
		_condition(std::move(condition)),
		_trueCase(std::move(trueCase)),
		_falseCase(std::move(falseCase))
		{}

	public:

		ConditionalExpressionSyntax(ConditionalExpressionSyntax&&) = default;
		ConditionalExpressionSyntax(const ConditionalExpressionSyntax&) = delete;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& condition() const { return _condition; }
		const auto& trueCase() const { return _trueCase; }
		const auto& falseCase() const { return _falseCase; }
	};
}

#endif
