#ifndef WARBLER_AST_LOOP_STATEMENT_H
#define WARBLER_AST_LOOP_STATEMENT_H

// local headers
#include <warbler/token.h>
#include <warbler/error.h>
#include <warbler/ast/loop_condition.h>
#include <warbler/ast/statement.h>

typedef enum LoopType
{
	LOOP_FOR,
	LOOP_WHILE,
	LOOP_LOOP
} LoopType;

typedef struct LoopStatement
{
	LoopType type;
	LoopCondition *condition;
	Statement *statement;
} LoopStatement;

Error loop_statement_parse(LoopStatement *loop, TokenIterator *iter);
void loop_statement_free(LoopStatement *loop);

#endif
