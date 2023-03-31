#ifndef PARKA_AST_STATMENT_EXPRESSION_HPP
#define PARKA_AST_STATMENT_EXPRESSION_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/statement/statement.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

#include <utility>

class ExpressionStatement : public Statement
{
	ExpressionId _expression;

	ExpressionStatement(ExpressionId&& expression) :
	_expression(std::move(expression))
	{}

public:

	ExpressionStatement(ExpressionStatement&&) = default;
	ExpressionStatement(const ExpressionStatement&) = delete;
	~ExpressionStatement() = default;

	static Optional<StatementId> parse(Token& token);

	bool validate(LocalSymbolTable& symbols);

	const auto& expression() const { return _expression; }
};

#endif
