
#include "parka/ast/expression/prefix.hpp"
#include "parka/ast/expression/postfix.hpp"

#include "parka/util/print.hpp"

Optional<Box<Expression>> Prefix::parse(Token& token)
{
	Prefix node = { 0 };

	switch (token.type())
	{
		case TokenType::Ampersand:
			node.type = PREFIX_REFERENCE;
			break;

		case TokenType::Asterisk:
			node.type = PREFIX_DEREFERENCE;
			break;

		case TokenType::Plus:
			node.type = PREFIX_POSITIVE;
			break;

		case TokenType::Minus:
			node.type = PREFIX_NEGATIVE;
			break;

		case TokenType::BitwiseNot:
			node.type = PREFIX_BITWISE_NOT;
			break;

		case TokenType::BooleanNot:
			node.type = PREFIX_BOOLEAN_NOT;
			break;

		default:
			return parsePostfix(out, token);
	}

	node.token = *token;

	token.increment();

	if (!parsePrefix(&node.expression, token))
		goto error;

	*makeNew(out->prefix) = node;
	out->type = EXPRESSION_PREFIX;

	return true;
	
error:

	return false;
}

bool Prefix::validate(SymbolTable& symbols)
{
	assert(node);
	exitNotImplemented();
}
