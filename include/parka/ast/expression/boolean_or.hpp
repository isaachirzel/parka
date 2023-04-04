#ifndef PARKA_AST_EXPRESSION_BOOLEAN_OR_HPP
#define PARKA_AST_EXPRESSION_BOOLEAN_OR_HPP

#include "parka/ast/expression/expression.hpp"

class BooleanOrExpression : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;

	BooleanOrExpression(ExpressionId&& lhs, ExpressionId&&rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BooleanOrExpression(BooleanOrExpression&&) = default;
	BooleanOrExpression(const BooleanOrExpression&) = delete;
	~BooleanOrExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType(Ref<Type> expected = {}) const;

	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
};

#endif
