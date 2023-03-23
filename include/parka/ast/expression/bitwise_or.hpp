#ifndef PARKA_AST_EXPRESSION_BITWISE_OR_HPP
#define PARKA_AST_EXPRESSION_BITWISE_OR_HPP

#include "parka/ast/expression/expression.hpp"

class BitwiseOrExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;

	BitwiseOrExpression(Box<Expression>&& lhs, Box<Expression>&&rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BitwiseOrExpression(BitwiseOrExpression&&) = default;
	BitwiseOrExpression(const BitwiseOrExpression&) = delete;
	~BitwiseOrExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& table);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
};

#endif
