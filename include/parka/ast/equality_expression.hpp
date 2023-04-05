#ifndef PARKA_AST_EXPRESSION_EQUALITY_HPP
#define PARKA_AST_EXPRESSION_EQUALITY_HPP

#include "parka/ast/expression.hpp"


enum EqualityType
{
	EQUALITY_EQUALS,
	EQUALITY_NOT_EQUALS
};

class EqualityExpression : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;
	EqualityType _type;

	EqualityExpression(ExpressionId&& lhs, ExpressionId&& rhs, EqualityType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

public:

	EqualityExpression(EqualityExpression&&) = default;
	EqualityExpression(const EqualityExpression&) = delete;
	~EqualityExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType() const;

	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
	const auto& type() const { return _type; }
};

#endif
