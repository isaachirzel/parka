
#ifndef PARKA_AST_EXPRESSION_CONDITIONAL_HPP
#define PARKA_AST_EXPRESSION_CONDITIONAL_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/symbol/local_symbol_table.hpp"
#include "parka/symbol/local_symbol_table.hpp"

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

	bool validate(LocalSymbolTable& symbols);
	Optional<Type> getType(const LocalSymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& condition() const { return _condition; }
	const auto& trueCase() const { return _trueCase; }
	const auto& falseCase() const { return _falseCase; }
};

#endif
