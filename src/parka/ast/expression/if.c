#include "parka/ast/expression/if.h"
#include "parka/ast/statement/statement.h"
#include "parka/util/memory.h"

void ifExpressionFree(IfExpression *node)
{
	expressionFree(&node->condition);
	statementFree(node->thenCase);

	if (node->type == IF_THEN_ELSE)
	{
		statementFree(node->elseCase);
	}
	else if (node->type == IF_THEN_ELSE)
	{
		ifExpressionFree(node->elseIf);
		deallocate(node->elseIf);
	}
}