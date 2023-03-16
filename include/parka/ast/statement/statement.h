#ifndef PARKA_AST_STATEMENT_H
#define PARKA_AST_STATEMENT_H

#include "parka/ast/expression/expression.h"

struct JumpStatement;
struct Declaration;

typedef enum StatementType
{
	STATEMENT_EXPRESSION,
	STATEMENT_DECLARATION,
	STATEMENT_JUMP
} StatementType;

typedef struct Statement
{
	union
	{
		struct Expression *expression;
		struct Declaration *declaration;
		struct JumpStatement *jump;
	};

	StatementType type;
} Statement;

bool parseStatement(Statement *out, Token *token);
bool validateStatement(Statement *node, LocalSymbolTable *localTable);
void statementFree(Statement *node);

#endif
