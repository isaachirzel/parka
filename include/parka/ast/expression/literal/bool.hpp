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

	BoolLiteral(BoolLiteral&&) = default;
	BoolLiteral(const BoolLiteral&) = delete;
	~BoolLiteral() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(LocalSymbolTable& symbols);
	Optional<Type> getType(const LocalSymbolTable& symbolTable, Ref<Type> expected = {}) const;
};

#endif
