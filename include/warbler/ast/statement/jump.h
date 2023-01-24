#ifndef WARBLER_AST_STATEMENT_JUMP_H
#define WARBLER_AST_STATEMENT_JUMP_H

#include "warbler/ast/expression/expression.h"
#include "warbler/token.h"

typedef enum JumpType
{
	JUMP_CONTINUE,
	JUMP_BREAK,
	JUMP_RETURN,
	JUMP_YIELD
} JumpType;

typedef struct JumpStatement
{
	Token token;
	JumpType type;
	Expression value;
	bool hasValue;
} JumpStatement;

bool parseJumpStatement(JumpStatement *out, Token *token);
bool validateJumpStatement(JumpStatement *node, LocalSymbolTable *localTable);
void jumpStatementFree(JumpStatement *node);

#endif
