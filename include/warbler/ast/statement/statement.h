#ifndef WARBLER_AST_STATEMENT_H
#define WARBLER_AST_STATEMENT_H

#include <warbler/ast/expression_statement.h>
#include <warbler/ast/declaration_statement.h>
#include <warbler/ast/compound_statement.h>
#include <warbler/ast/selection_statement.h>
#include <warbler/ast/loop_statement.h>
#include <warbler/ast/jump_statement.h>

typedef enum StatementType
{
	STATEMENT_EXPRESSION,
	STATEMENT_DECLARATION,
	STATEMENT_COMPOUND,
	STATEMENT_SELECTION,
	STATEMENT_LOOP,
	STATEMENT_JUMP
} StatementType;

typedef struct Statement
{
	StatementType type;

	union
	{
		ExpressionStatement expression;
		DeclarationStatement declaration;
		CompoundStatement compound;
		SelectionStatment selection;
		LoopStatement loop;
		JumpStatement jump;
	};
} Statement;

#endif
