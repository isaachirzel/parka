#ifndef PARKA_AST_EXPRESSION_BITWISE_OR_HPP
#define PARKA_AST_EXPRESSION_BITWISE_OR_HPP

#include "parka/ast/expression/expression.hpp"

class BitwiseOrExpression : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;

	BitwiseOrExpression(ExpressionId&& lhs, ExpressionId&&rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BitwiseOrExpression(BitwiseOrExpression&&) = default;
	BitwiseOrExpression(const BitwiseOrExpression&) = delete;
	~BitwiseOrExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(LocalSymbolTable& table);
	Optional<Type> getType(const LocalSymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
};

#endif
