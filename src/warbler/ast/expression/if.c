#include "warbler/ast/expression/if.h"
#include "warbler/ast/statement/statement.h"
#include "warbler/util/memory.h"

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