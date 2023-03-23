#ifndef PARKA_AST_EXPRESSION_BITWISE_XOR_HPP
#define PARKA_AST_EXPRESSION_BITWISE_XOR_HPP

#include "parka/ast/expression/expression.hpp"

class BitwiseXorExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;

	BitwiseXorExpression(Box<Expression>&& lhs, Box<Expression>&&rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

public:

	BitwiseXorExpression(BitwiseXorExpression&&) = default;
	BitwiseXorExpression(const BitwiseXorExpression&) = delete;
	~BitwiseXorExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& table);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
};

#endif
