#ifndef PARKA_AST_EXPRESSION_ADDITIVE_HPP
#define PARKA_AST_EXPRESSION_ADDITIVE_HPP

#include "parka/ast/expression.hpp"

#include <utility>

enum class AdditiveType
{
	Add,
	Subtract
};

class AdditiveExpression : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;
	AdditiveType _type;

	AdditiveExpression(ExpressionId&& lhs, ExpressionId&& rhs, AdditiveType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}
	
public:

	AdditiveExpression(AdditiveExpression&&) = default;
	AdditiveExpression(const AdditiveExpression&) = delete;
	~AdditiveExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType() const;

	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
	const auto& type() const { return _type; }
};

#endif
