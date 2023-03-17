#include "parka/ast/statement/statement.h"
#include "parka/ast/statement/declaration.h"
#include "parka/ast/statement/jump.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseStatement(Statement *out, Token *token)
{
	switch (token->type)
	{
		case TOKEN_KEYWORD_VAR:
		{
			Declaration declaration;

			if (!parseDeclaration(&declaration, token))
				return false;

			*makeNew(out->declaration) = declaration;
			out->type = STATEMENT_DECLARATION;

			return true;
		}

		case TOKEN_KEYWORD_RETURN:
		case TOKEN_KEYWORD_BREAK:
		case TOKEN_KEYWORD_CONTINUE:
		case TOKEN_KEYWORD_YIELD:
		{
			JumpStatement jump;

			if (!parseJumpStatement(&jump, token))
				return false;

			*makeNew(out->jump) = jump;
			out->type = STATEMENT_JUMP;

			return true;
		}

		default:
			break;
	}

	Expression expression;

	if (!parseExpression(&expression, token))
		return false;

	if (token->type != TOKEN_SEMICOLON)
	{
		printParseError(token, "';' after expression statement", NULL);
		expressionFree(&expression);
		return false;
	}

	incrementToken(token);

	*makeNew(out->expression) = expression;
	out->type = STATEMENT_EXPRESSION;

	return true;
}

bool validateStatement(Statement *node, LocalSymbolTable *localTable)
{
	printFmt("Statement type: %d", node->type);

	switch (node->type)
	{
		case STATEMENT_EXPRESSION:
			return validateExpression(node->expression, localTable);

		case STATEMENT_DECLARATION:
			return validateDeclaration(node->declaration, localTable);

		case STATEMENT_JUMP:
			return validateJumpStatement(node->jump, localTable);

		default:
			break;
	}

	exitWithErrorFmt("Unable to validate Statement with StatementType: %d", node->type);
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
