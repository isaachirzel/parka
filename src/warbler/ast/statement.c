#include "warbler/ast/statement.h"
#include "warbler/ast/type.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"

void jumpStatementFree(JumpStatement *node)
{
	if (node->hasValue)
		expressionFree(&node->value);
}

void statementFree(Statement *node)
{
	switch (node->type)
	{
		case STATEMENT_EXPRESSION:
			expressionFree(node->expression);
			deallocate(node->expression);
			break;

		case STATEMENT_DECLARATION:
			declarationFree(node->declaration);
			deallocate(node->declaration);
			break;

		case STATEMENT_JUMP:
			jumpStatementFree(node->jump);
			deallocate(node->jump);
			break;

		default:
			exitWithErrorFmt("Unable to free Statement with StatementType: %d", node->type);
	}
}

void variableFree(Variable *node)
{
	typeAnnotationFree(&node->annotation);
	deallocate(node->symbol);
}

void declarationFree(Declaration *node)
{
	expressionFree(&node->value);
}
