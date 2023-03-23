#ifndef PARKA_AST_EXPRESSION_MULTIPLICATIVE_HPP
#define PARKA_AST_EXPRESSION_MULTIPLICATIVE_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/symbol_table.hpp"
#include "parka/util/optional.hpp"

#include <utility>

typedef enum MultiplicativeType
{
	MULTIPLICATIVE_MULTIPLY,
	MULTIPLICATIVE_DIVIDE,
	MULTIPLICATIVE_MODULUS
} MultiplicativeType;

class MultiplicativeExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;
	MultiplicativeType _type;

	MultiplicativeExpression(Box<Expression>&& lhs, Box<Expression>&& rhs, MultiplicativeType type):
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

public:

	MultiplicativeExpression(MultiplicativeExpression&&) = default;
	MultiplicativeExpression(const MultiplicativeExpression&) = delete;
	~MultiplicativeExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
	const auto& type() const { return _type; }
};

#endif
