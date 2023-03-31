#ifndef PARKA_AST_EXPRESSION_RELATIONAL_HPP
#define PARKA_AST_EXPRESSION_RELATIONAL_HPP

#include "parka/ast/expression/expression.hpp"


enum class RelationalType
{
	GreaterThan,
	LessThan,
	GreaterThanOrEqualTo,
	LessThanOrEqualTo
};

class RelationalExpression : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;
	RelationalType _type;

	RelationalExpression(ExpressionId&& lhs, ExpressionId&& rhs, RelationalType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

public:

	RelationalExpression(RelationalExpression&&) = default;
	RelationalExpression(const RelationalExpression&) = delete;
	~RelationalExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(LocalSymbolTable& symbols);
	Optional<Type> getType(const LocalSymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
	const auto& type() const { return _type; }
};

#endif
