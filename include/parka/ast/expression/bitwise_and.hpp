#ifndef PARKA_AST_EXPRESSION_BITWISE_AND_HPP
#define PARKA_AST_EXPRESSION_BITWISE_AND_HPP

#include "parka/ast/expression/expression.hpp"

class BitwiseAndExpression : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;

	BitwiseAndExpression(ExpressionId&& lhs, ExpressionId&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BitwiseAndExpression(BitwiseAndExpression&&) = default;
	BitwiseAndExpression(const BitwiseAndExpression&) = delete;
	~BitwiseAndExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType(Ref<Type> expected = {}) const;

	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
};

#endif
