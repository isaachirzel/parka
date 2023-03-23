#ifndef PARKA_AST_EXPRESSION_BOOLEAN_AND_HPP
#define PARKA_AST_EXPRESSION_BOOLEAN_AND_HPP

#include "parka/ast/expression/expression.hpp"

class BooleanAndExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;

	BooleanAndExpression(Box<Expression>&& lhs, Box<Expression>&&rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BooleanAndExpression(BooleanAndExpression&&) = default;
	BooleanAndExpression(const BooleanAndExpression&) = delete;
	~BooleanAndExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& table);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
};

#endif
