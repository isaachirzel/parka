#ifndef PARKA_AST_EXPRESSION_ADDITIVE_HPP
#define PARKA_AST_EXPRESSION_ADDITIVE_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/util/box.hpp"

class SymbolTable;

#include <utility>

enum AdditiveType
{
	ADDITIVE_ADD,
	ADDITIVE_SUBTRACT
};

class AdditiveExpression : public Expression
{
	Box<Expression> _lhs;
	Box<Expression> _rhs;
	AdditiveType _type;

	AdditiveExpression(Box<Expression>&& lhs, Box<Expression>&& rhs, AdditiveType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}
	
public:

	AdditiveExpression(AdditiveExpression&&) = default;
	AdditiveExpression(const AdditiveExpression&) = delete;
	~AdditiveExpression() = default;

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& lhs() const { return *_lhs; }
	const auto& rhs() const { return *_rhs; }
	const auto& type() const { return _type; }
};

#endif
