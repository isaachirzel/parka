#ifndef PARKA_AST_EXPRESSION_EQUALITY_HPP
#define PARKA_AST_EXPRESSION_EQUALITY_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/symbol_table.hpp"

enum EqualityType
{
	EQUALITY_EQUALS,
	EQUALITY_NOT_EQUALS
};

class EqualityExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;
	EqualityType _type;

	EqualityExpression(Box<Expression>&& lhs, Box<Expression>&& rhs, EqualityType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

public:

	EqualityExpression(EqualityExpression&&) = default;
	EqualityExpression(const EqualityExpression&) = delete;
	~EqualityExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
	const auto& type() const { return _type; }
};

#endif
