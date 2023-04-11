
#ifndef PARKA_SYNTAX_EXPRESSION_CONDITIONAL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CONDITIONAL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class ConditionalExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _condition;
		ExpressionId _trueCase;
		ExpressionId _falseCase;

		ConditionalExpressionSyntax(ExpressionId&& condition, ExpressionId&& trueCase, ExpressionId&& falseCase) :
		_condition(std::move(condition)),
		_trueCase(std::move(trueCase)),
		_falseCase(std::move(falseCase))
		{}

	public:

		ConditionalExpressionSyntax(ConditionalExpressionSyntax&&) = default;
		ConditionalExpressionSyntax(const ConditionalExpressionSyntax&) = delete;
		~ConditionalExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		const auto& condition() const { return _condition; }
		const auto& trueCase() const { return _trueCase; }
		const auto& falseCase() const { return _falseCase; }
	};
}

#endif
