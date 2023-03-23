#ifndef PARKA_AST_EXPRESSION_LITERAL_BOOL_HPP
#define PARKA_AST_EXPRESSION_LITERAL_BOOL_HPP

#include "parka/ast/expression/literal/literal.hpp"

class BoolLiteral : public Literal
{
	Token _token;
	bool _value;

	BoolLiteral(const Token& token, bool value) :
	_token(token),
	_value(value)
	{}

public:

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& symbols);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;
};

#endif
