#include "parka/ast/expression/conditional.h"
#include "parka/ast/expression/boolean_or.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseConditionalExpression(Expression *out, Token *token)
{
	ConditionalExpression node = { 0 };

	if (!parseBooleanOrExpression(&node.expression, token))
		goto error;

	if (token->type != TOKEN_KEYWORD_THEN)
	{
		*out = node.expression;
		return true;
	}

	incrementToken(token);

	node.hasRhs = true;

	if (!parseBooleanOrExpression(&node.rhs.trueCase, token))
		goto error;

	if (token->type != TOKEN_KEYWORD_ELSE)
	{
		printParseError(token, "'else' or false case", NULL);
		goto error;
	}

	incrementToken(token);

	if (!parseBooleanOrExpression(&node.rhs.falseCase, token))
		goto error;

	out->type = EXPRESSION_CONDITIONAL;
	*makeNew(out->conditional) = node;

	return true;
	
error:

	conditionalExpressionFree(&node);
	return false;
}

void freeConditionalRhs(ConditionalRhs *node)
{
	expressionFree(&node->trueCase);
	expressionFree(&node->falseCase);
}

void conditionalExpressionFree(ConditionalExpression *node)
{
	expressionFree(&node->expression);

	if (node->hasRhs)
		freeConditionalRhs(&node->rhs);
}
