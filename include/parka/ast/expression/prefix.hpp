#ifndef PARKA_AST_EXPRESSION_PREFIX_HPP
#define PARKA_AST_EXPRESSION_PREFIX_HPP

#include "parka/ast/expression/expression.hpp"

#include "parka/token.hpp"

enum class PrefixType
{
	Reference,
	Dereference,
	Positive,
	Negative,
	BitwiseNot,
	BooleanNot
};

class Prefix : public Expression
{
	Token _token;
	ExpressionId _expression;
	PrefixType _type;

	Prefix(PrefixType type, ExpressionId&& expression, const Token& token) :
	_token(token),
	_expression(std::move(expression)),
	_type(type)
	{}

public:

	Prefix(Prefix&&) = default;
	Prefix(const Prefix&) = delete;
	~Prefix() = default;

	static Optional<ExpressionId> parse(Token& token);
	
	bool validate(LocalSymbolTable& symbols);
	Optional<Type> getType(const LocalSymbolTable& symbolTable, Ref<Type> expected = {}) const;

	const auto& token() const { return _token; }
	const auto& expression() const { return _expression; }
	const auto& type() const { return _type; }
};

#endif
