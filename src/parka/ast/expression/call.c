#include "parka/ast/expression/call.h"
#include "parka/symbol_table.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseCallExpression(CallExpression* out, Token *token)
{
	assert(token->type == TOKEN_LEFT_PARENTHESIS);
	incrementToken(token);

	CallExpression node = { 0 };

parseArgument:

	if (token->type != TOKEN_RIGHT_PARENTHESIS)
	{
		incrementToken(token);

		Expression expression;

		if (!parseExpression(&expression, token))
			goto error;
		
		resizeArray(node.expressions, ++node.count);
		node.expressions[node.count - 1] = expression;

		if (token->type == TOKEN_COMMA)
		{
			incrementToken(token);
			goto parseArgument;
		}

		if (token->type != TOKEN_RIGHT_PARENTHESIS)
		{
			printParseError(token, "')' after function arguments", NULL);
			return false;
		}
	}

	incrementToken(token);

	*out = node;

	// return arguments
	return true;
	
error:

	callExpressionFree(&node);
	return false;
}

bool validateCallExpression(CallExpression *node, LocalSymbolTable *localTable)
{
	assert(node);
	exitNotImplemented();
}

void callExpressionFree(CallExpression *node)
{
	for (usize i = 0; i < node->count; ++i)
		expressionFree(&node->expressions[i]);

	deallocate(node->expressions);
}