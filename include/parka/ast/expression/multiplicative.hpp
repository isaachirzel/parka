#ifndef PARKA_AST_EXPRESSION_MULTIPLICATIVE_HPP
#define PARKA_AST_EXPRESSION_MULTIPLICATIVE_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/util/optional.hpp"

#include <utility>

enum MultiplicativeType
{
	MULTIPLICATIVE_MULTIPLY,
	MULTIPLICATIVE_DIVIDE,
	MULTIPLICATIVE_MODULUS
};

class MultiplicativeExpression : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;
	MultiplicativeType _type;

	MultiplicativeExpression(ExpressionId&& lhs, ExpressionId&& rhs, MultiplicativeType type):
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

public:

	MultiplicativeExpression(MultiplicativeExpression&&) = default;
	MultiplicativeExpression(const MultiplicativeExpression&) = delete;
	~MultiplicativeExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType() const;

	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
	const auto& type() const { return _type; }
};

#endif
