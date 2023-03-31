#ifndef PARKA_AST_EXPRESSION_SHIFT_HPP
#define PARKA_AST_EXPRESSION_SHIFT_HPP

#include "parka/ast/expression/expression.hpp"

enum class BitShiftType
{
	Left,
	Right
};

class BitShiftExpression : public Expression
{
	ExpressionId _lhs;
	ExpressionId _rhs;
	BitShiftType _type;

	BitShiftExpression(ExpressionId&& lhs, ExpressionId&& rhs, BitShiftType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

public:

	BitShiftExpression(BitShiftExpression&&) = default;
	BitShiftExpression(const BitShiftExpression&) = delete;
	~BitShiftExpression() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(LocalSymbolTable& symbols);
	Optional<Type> getType(const LocalSymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& lhs() const { return _lhs; }
	const auto& rhs() const { return _rhs; }
};

#endif
