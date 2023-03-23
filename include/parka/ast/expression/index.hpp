#ifndef PARKA_AST_EXPRESSION_INDEX_HPP
#define PARKA_AST_EXPRESSION_INDEX_HPP

#include "parka/ast/expression/expression.hpp"

#include <utility>

class IndexExpression : public Expression
{
	Box<Expression> _expression;
	Box<Expression> _index;

	IndexExpression(Box<Expression>&& expression, Box<Expression>&& index) :
	_expression(std::move(expression)),
	_index(std::move(index))
	{}

public:

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& expression() const { return *_expression; }
	const auto& index() const { return _index; }
};

#endif
