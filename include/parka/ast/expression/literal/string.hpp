#ifndef PARKA_AST_EXPRESSION_LITERAL_STRING_HPP
#define PARKA_AST_EXPRESSION_LITERAL_STRING_HPP

#include "parka/ast/expression/literal/literal.hpp"

class StringLiteral : public Literal
{
	Token _token;
	String _value;

	StringLiteral(Token token, String&& value) :
	_token(token),
	_value(std::move(value))
	{}

public:

	StringLiteral(StringLiteral&&) = default;
	StringLiteral(const StringLiteral&) = delete;
	~StringLiteral() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(SymbolTable& symbols);
	Optional<Type> getType(const SymbolTable& symbolTable, Ref<Type> expected = {}) const;
};

#endif
