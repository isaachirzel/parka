#ifndef PARKA_AST_EXPRESSION_CONDITIONAL_HPP
#define PARKA_AST_EXPRESSION_CONDITIONAL_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/symbol_table.hpp"

class ConditionalExpression : public Expression
{
	Box<Expression> _condition;
	Box<Expression> _trueCase;
	Box<Expression> _falseCase;

	ConditionalExpression(Box<Expression>&& condition, Box<Expression>&& trueCase, Box<Expression>&& falseCase) :
	_condition(std::move(condition)),
	_trueCase(std::move(trueCase)),
	_falseCase(std::move(falseCase))
	{}

public:

	ConditionalExpression(ConditionalExpression&&) = default;
	ConditionalExpression(const ConditionalExpression&) = delete;
	~ConditionalExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& condition() const { return *_condition; }
	const auto& trueCase() const { return *_trueCase; }
	const auto& falseCase() const { return *_falseCase; }
};

#endif
