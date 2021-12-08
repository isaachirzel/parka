#ifndef WARBLER_AST_H
#define WARBLER_AST_H

// local
#include <warbler/string.h>

typedef struct Typename
{
	const String *text;
} Typename;

typedef struct Label
{
	const String *text;
} Label;

typedef struct Parameter
{
	const String *text;
} Parameter;

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

typedef struct UnaryExpression
{

} UnaryExpression;

typedef enum AssignmentType
{
	ASSIGN_NONE,
	ASSIGN_BECOME,
	ASSIGN_MULTIPLY,
	ASSIGN_DIVIDE,
	ASSIGN_MODULUS,
	ASSIGN_ADD,
	ASSIGN_SUBTRACT,
	ASSIGN_LSHIFT,
	ASSIGN_RSHIFT,
	ASSIGN_BITWISE_AND,
	ASSIGN_BITWISE_OR,
	ASSIGN_BITWISE_XOR,
	ASSIGN_BOOLEAN_AND,
	ASSIGN_BOOLEAN_XOR,
	ASSIGN_BOOLEAN_OR
} AssignmentType;

struct Expression;

typedef struct AssignmentExpression
{
	UnaryExpression *left;
	struct Expression *right;
	AssignmentType type;
} AssignmentExpression;

typedef struct Expression
{
	AssignmentExpression *assignment;
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
