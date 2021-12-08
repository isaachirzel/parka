#ifndef WARBLER_AST_H
#define WARBLER_AST_H

// local
#include <warbler/string.h>

typedef struct Typename
{
	const String *text;
} Typename;

typedef struct Identifier
{
	const String *text;
} Identifier;

typedef enum StatementType
{
	STMT_INVALID
} StatementType;

typedef struct Statement
{
	StatementType type;

} Statement;

typedef enum ExpressionType
{
	EXPR_INVALID
} ExpressionType;

typedef struct Expression
{
	ExpressionType type;
} Expression;

typedef struct Function
{
	const Identifier *identifier;

} Function;

typedef struct Module
{
	Function *functions;
	size_t count;
} Module;

typedef struct Program
{
	Module *modules;
	size_t count;
} Program;

void program_free(Program *program);
void module_free(Module *module);
void typename_free(Typename *typename);
void identifier_free(Identifier *identifier);
void function_free(Function *function);
void statement_free(Statement *statement);
void expression_free(Expression *expression);

#endif
