#ifndef WARBLER_AST_JUMP_STATEMENT_H
#define WARBLER_AST_JUMP_STATEMENT_H

// local headers
#include <warbler/token.h>
#include <warbler/error.h>
#include <warbler/ast/expression.h>

typedef enum JumpType
{
	JUMP_CONTINUE,
	JUMP_BREAK,
	JUMP_RETURN,
	JUMP_EMIT
} JumpType;

typedef struct JumpStatement
{
	JumpType type;
	Expression *value;
} JumpStatement;

Error jump_statement_parse(JumpStatement *jump, TokenIterator *iter);
void jump_statement_free(JumpStatement *jump);

#endif
