#ifndef PARKA_AST_EXPRESSION_PREFIX_HPP
#define PARKA_AST_EXPRESSION_PREFIX_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/symbol_table.hpp"
#include "parka/token.hpp"

enum PrefixType
{
	PREFIX_REFERENCE,
	PREFIX_DEREFERENCE,
	PREFIX_POSITIVE,
	PREFIX_NEGATIVE,
	PREFIX_BITWISE_NOT,
	PREFIX_BOOLEAN_NOT
};

class Prefix : public Expression
{
	Token _token;
	Box<Expression> _expression;
	PrefixType _type;

	Prefix(const Token& token, Box<Expression>&& expression, PrefixType type) :
	_token(token),
	_expression(std::move(expression)),
	_type(type)
	{}

public:

	Prefix(Prefix&&) = default;
	Prefix(const Prefix&) = delete;
	~Prefix() = default;

	static Optional<Box<Expression>> parse(Token& token);
	
	bool validate(SymbolTable& localTable);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;;

	const auto& token() const { return _token; }
	const auto& expression() const { return *_expression; }
	const auto& type() const { return _type; }
};

#endif
