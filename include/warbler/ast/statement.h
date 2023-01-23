#ifndef WARBLER_AST_STATEMENT_H
#define WARBLER_AST_STATEMENT_H

#include "warbler/ast/expression.h"

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

typedef struct JumpStatement
{
	Token token;
	JumpType type;
	Expression value;
	bool hasValue;
} JumpStatement;

typedef struct Variable
{
	Token name;
	char *symbol;
	TypeAnnotation annotation;
	bool isMutable;
	bool isExplicitlyTyped;
} Variable;

typedef struct Declaration
{
	usize variableId;
	Expression value;
} Declaration;

void statementFree(Statement *node);
void jumpStatementFree(JumpStatement *node);
void variableFree(Variable *node);
void declarationFree(Declaration *node);

#endif
