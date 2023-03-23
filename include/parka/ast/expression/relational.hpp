#ifndef PARKA_AST_EXPRESSION_RELATIONAL_HPP
#define PARKA_AST_EXPRESSION_RELATIONAL_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/symbol_table.hpp"

typedef enum RelationalType
{
	RELATIONAL_GREATER_THAN,
	RELATIONAL_LESS_THAN,
	RELATIONAL_GREATER_THAN_OR_EQUAL_TO,
	RELATIONAL_LESS_THAN_OR_EQUAL_TO
} RelationalType;

class RelationalExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;
	RelationalType _type;

	RelationalExpression(Box<Expression>&& lhs, Box<Expression>&& rhs, RelationalType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

public:

	RelationalExpression(RelationalExpression&&) = default;
	RelationalExpression(const RelationalExpression&) = delete;
	~RelationalExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
	const auto& type() const { return _type; }
};

#endif
