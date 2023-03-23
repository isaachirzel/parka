#ifndef PARKA_AST_EXPRESSION_SHIFT_HPP
#define PARKA_AST_EXPRESSION_SHIFT_HPP

#include "parka/ast/expression/expression.hpp"

enum BitShiftType
{
	BIT_SHIFT_LEFT,
	BIT_SHIFT_RIGHT
};

class BitShiftExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;

	BitShiftExpression(Box<Expression>&& lhs, Box<Expression>&& rhs):
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BitShiftExpression(BitShiftExpression&&) = default;
	BitShiftExpression(const BitShiftExpression&) = delete;
	~BitShiftExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
};

#endif
