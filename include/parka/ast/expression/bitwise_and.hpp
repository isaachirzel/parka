#ifndef PARKA_AST_EXPRESSION_BITWISE_AND_HPP
#define PARKA_AST_EXPRESSION_BITWISE_AND_HPP

#include "parka/ast/expression/expression.hpp"

class BitwiseAndExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;

	BitwiseAndExpression(Box<Expression>&& lhs, Box<Expression>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BitwiseAndExpression(BitwiseAndExpression&&) = default;
	BitwiseAndExpression(const BitwiseAndExpression&) = delete;
	~BitwiseAndExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& table);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
};

#endif
