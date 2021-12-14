#ifndef WARBLER_AST_FUNCTION_H
#define WARBLER_AST_FUNCTION_H

// local headers
#include <warbler/ast/typename.h>
#include <warbler/ast/identifier.h>
#include <warbler/ast/parameter.h>
#include <warbler/ast/expression/expression.h>
#include <warbler/ast/statement/compound.h>

// standard headers
#include <stdbool.h>

typedef struct Function
{
	Identifier name;
	Typename return_type;
	ParameterList *parameters;

	bool is_inline;
	union
	{
		CompoundStatement *compound;
		Expression *expression;
	} body;
} Function;

void function_init(Function *function);
void function_free(Function *function);
Error function_parse(Function *function, TokenIterator *iter);

#endif
