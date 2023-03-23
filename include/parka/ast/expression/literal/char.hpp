#ifndef PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP
#define PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP

#include "parka/ast/expression/literal/literal.hpp"

class CharLiteral : public Literal
{
	Token _token;
	char _value;
	// TODO: UTF-8

	CharLiteral(const Token& token, char value) :
	_token(token),
	_value(value)
	{}

public:

	static Optional<Box<Expression>> parse(Token& token);

	bool validate(SymbolTable& symbols);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;
}

#endif
