#include "warbler/ast/expression/postfix.h"
#include "warbler/ast/expression/call.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"

bool parsePostfix(Expression *out, Token *token)
{
	Postfix node = { 0 };

	if (!parsePrimaryExpression(&node.expression, token))
		goto error;

parsePostfix:

	switch (token->type)
	{
		case TOKEN_LEFT_BRACKET: // Index
			incrementToken(token);

			Expression index;

			if (!parseExpression(&index, token))
				goto error;

			node.type = POSTFIX_INDEX;
			node.index = index;

			if (token->type != TOKEN_RIGHT_BRACKET)
			{
				printParseError(token, "']' after index operation", NULL);
				goto error;
			}

			incrementToken(token);
			break;

		case TOKEN_LEFT_PARENTHESIS: // Function call
		{
			CallExpression arguments;

			if (!parseCallExpression(&arguments, token))
				goto error;

			node.type = POSTFIX_FUNCTION_CALL;
			node.call = arguments;
			break;
		}

		case TOKEN_DOT: // Member
			incrementToken(token);
		
			if (token->type != TOKEN_IDENTIFIER)
			{
				printParseError(token, "member, method, or property name", NULL);
				goto error;
			}

			Token name = *token;

			incrementToken(token);
			
			node.type = POSTFIX_MEMBER;
			node.member = name;
			break;
		
		default:
			goto finish;
	}

	Expression inner =
	{
		.type = EXPRESSION_POSTFIX,
		.postfix = new(Postfix)
	};

	*inner.postfix = node;

	node = (Postfix)
	{
		.expression = inner
	};

	goto parsePostfix;

finish:

	*out = node.expression;

	return true;
	
error:

	postfixFree(&node);
	return false;
}

bool validatePostfix(Postfix *node, LocalSymbolTable *localTable)
{
	if (!validateExpression(&node->expression, localTable))
		return false;
	
	switch (node->type)
	{
		case POSTFIX_INDEX:
			exitWithError("Postfix indexing not implemented");
			break;

		case POSTFIX_FUNCTION_CALL:
			exitWithError("Postfix function call not implemented");
			break;

		case POSTFIX_MEMBER:
			exitWithError("Postfix member validation not implemented");
			break;
	}

	return true;
}

void postfixFree(Postfix *node)
{
	expressionFree(&node->expression);

	switch (node->type)
	{
		case POSTFIX_INDEX:
			expressionFree(&node->index);
			break;

		case POSTFIX_FUNCTION_CALL:
			callExpressionFree(&node->call);
			break;

		case POSTFIX_MEMBER:
			break;

		default:
			exitWithErrorFmt("Invalid ExpressionType: %d", node->type);
	}
}
