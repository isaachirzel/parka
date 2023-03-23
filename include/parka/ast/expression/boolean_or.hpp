#ifndef PARKA_AST_EXPRESSION_BOOLEAN_OR_HPP
#define PARKA_AST_EXPRESSION_BOOLEAN_OR_HPP

#include "parka/ast/expression/expression.hpp"

class BooleanOrExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;

	BooleanOrExpression(Box<Expression>&& lhs, Box<Expression>&&rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BooleanOrExpression(BooleanOrExpression&&) = default;
	BooleanOrExpression(const BooleanOrExpression&) = delete;
	~BooleanOrExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& table);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
};

#endif
