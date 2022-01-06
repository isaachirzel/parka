#ifndef WARBLER_AST_FUNCTION_H
#define WARBLER_AST_FUNCTION_H

// local headers
#include <warbler/ast/typename.h>
#include <warbler/ast/identifier.h>
#include <warbler/ast/parameter.h>
#include <warbler/ast/expression/expression.h>
#include <warbler/ast/statement/compound_statement.h>

// standard headers
#include <stdbool.h>

typedef struct Function
{
	Identifier name;
	ParameterList parameters;
	Typename return_type;

	union
	{
		Expression *inline_body;
		CompoundStatement *compound_body;
	};
	
	bool is_inline;
} Function;

void function_init(Function *function);
void function_free(Function *function);
Error function_parse(Function *function, TokenIterator *iter);

#endif
