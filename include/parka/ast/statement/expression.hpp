#ifndef PARKA_AST_STATMENT_EXPRESSION_HPP
#define PARKA_AST_STATMENT_EXPRESSION_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/statement/statement.hpp"
#include "parka/util/optional.hpp"

#include <utility>

class ExpressionStatment : public Statement
{
	Box<Expression> _expression;

	ExpressionStatment(Box<Expression>&& expression) :
	_expression(std::move(expression))
	{}

public:

	ExpressionStatment(ExpressionStatment&&) = default;
	ExpressionStatment(const ExpressionStatment&) = delete;
	~ExpressionStatment() = default;

	static Optional<Box<Statement>> parse(Token& token);

	bool validate(SymbolTable& localTable);

	const auto& expression() const { return *_expression; }
}

#endif
