#ifndef PARKA_AST_EXPRESSION_LITERAL_INTEGER_HPP
#define PARKA_AST_EXPRESSION_LITERAL_INTEGER_HPP

#include "parka/ast/expression.hpp"
#include "parka/util/primitives.hpp"
#include "parka/ast/literal.hpp"

class IntegerLiteral : public Literal
{
	Token _token;
	u64 _value;
	u32 _bytes;

	IntegerLiteral(const Token& token, u64 value, u32 bytes) :
	_token(token),
	_value(value),
	_bytes(bytes)
	{}

public:

	IntegerLiteral(IntegerLiteral&&) = default;
	IntegerLiteral(const IntegerLiteral&) = delete;
	~IntegerLiteral() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType() const;
};

#endif
