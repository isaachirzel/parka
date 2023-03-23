#ifndef PARKA_AST_EXPRESSION_LITERAL_FLOAT_HPP
#define PARKA_AST_EXPRESSION_LITERAL_FLOAT_HPP

#include "parka/ast/expression/literal/literal.hpp"

class FloatLiteral : public Literal
{
	Token _token;
	double _value;

	FloatLiteral(const Token& token, double value) :
	_token(token),
	_value(value)
	{}

public:

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& symbols);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;
};

#endif
