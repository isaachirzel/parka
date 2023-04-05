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

	CharLiteral(CharLiteral&&) = default;
	CharLiteral(const CharLiteral&) = delete;
	~CharLiteral() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType() const;
};

#endif
