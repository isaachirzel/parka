#ifndef PARKA_AST_EXPRESSION_LITERAL_INTEGER_HPP
#define PARKA_AST_EXPRESSION_LITERAL_INTEGER_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/util/primitives.hpp"
#include "parka/ast/expression/literal/literal.hpp"

class IntegerLiteral : public Literal
{
	Token _token;
	u64 _value;
	u32 _bits;

	IntegerLiteral(const Token& token, u64 value, u32 bits) :
	_token(token),
	_value(value),
	_bits(bits)
	{}

public:

	IntegerLiteral(IntegerLiteral&&) = default;
	IntegerLiteral(const IntegerLiteral&) = delete;
	~IntegerLiteral() = default;

	static Optional<ExpressionId> parse(Token& token);

	bool validate(const EntityId& functionId);
	Optional<Type> getType(Ref<Type> expected = {}) const;
};

#endif
