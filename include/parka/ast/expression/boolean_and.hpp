#ifndef PARKA_AST_EXPRESSION_BOOLEAN_AND_HPP
#define PARKA_AST_EXPRESSION_BOOLEAN_AND_HPP

#include "parka/ast/expression/expression.hpp"

class BooleanAndExpression : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;

	BooleanAndExpression(ExpressionId&& lhs, ExpressionId&&rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BooleanAndExpression(BooleanAndExpression&&) = default;
	BooleanAndExpression(const BooleanAndExpression&) = delete;
	~BooleanAndExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(LocalSymbolTable& table);
	Optional<Type> getType(const LocalSymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
};

#endif
