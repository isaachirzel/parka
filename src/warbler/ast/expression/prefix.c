
#include "warbler/ast/expression/prefix.h"
#include "warbler/ast/expression/postfix.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"

bool parsePrefix(Expression *out, Token *token)
{
	Prefix node = { 0 };

	switch (token->type)
	{
		case TOKEN_AMPERSAND:
			node.type = PREFIX_REFERENCE;
			break;

		case TOKEN_ASTERISK:
			node.type = PREFIX_DEREFERENCE;
			break;

		case TOKEN_PLUS:
			node.type = PREFIX_POSITIVE;
			break;

		case TOKEN_MINUS:
			node.type = PREFIX_NEGATIVE;
			break;

		case TOKEN_BITWISE_NOT:
			node.type = PREFIX_BITWISE_NOT;
			break;

		case TOKEN_BOOLEAN_NOT:
			node.type = PREFIX_BOOLEAN_NOT;
			break;

		default:
			return parsePostfix(out, token);
	}

	node.token = *token;

	incrementToken(token);

	if (!parsePrefix(&node.expression, token))
		goto error;

	*makeNew(out->prefix) = node;
	out->type = EXPRESSION_PREFIX;

	return true;
	
error:

	prefixFree(&node);
	return false;
}

bool validatePrefix(Prefix *node, LocalSymbolTable *localTable)
{
	assert(node);
	exitNotImplemented();
}

void prefixFree(Prefix *node)
{
	expressionFree(&node->expression);
}
