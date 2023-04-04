
#ifndef PARKA_AST_EXPRESSION_CONDITIONAL_HPP
#define PARKA_AST_EXPRESSION_CONDITIONAL_HPP

#include "parka/ast/expression/expression.hpp"

class ConditionalExpression : public Expression
{
	ExpressionId _condition;
	ExpressionId _trueCase;
	ExpressionId _falseCase;

	ConditionalExpression(ExpressionId&& condition, ExpressionId&& trueCase, ExpressionId&& falseCase) :
	_condition(std::move(condition)),
	_trueCase(std::move(trueCase)),
	_falseCase(std::move(falseCase))
	{}

public:

	ConditionalExpression(ConditionalExpression&&) = default;
	ConditionalExpression(const ConditionalExpression&) = delete;
	~ConditionalExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType(Ref<Type> expected = {}) const;

	const auto& condition() const { return _condition; }
	const auto& trueCase() const { return _trueCase; }
	const auto& falseCase() const { return _falseCase; }
};

#endif
