#ifndef WARBLER_AST_FUNCTION_H
#define WARBLER_AST_FUNCTION_H

// local headers
#include <warbler/ast/typename.h>
#include <warbler/ast/identifier.h>
#include <warbler/ast/expression/expression.h>
#include <warbler/ast/statement/compound.h>

// standard headers
#include <stdbool.h>

typedef struct
{
	Typename return_type;
	Identifier name;
	bool is_inline;
	union
	{
		Expression *expression;
		CompoundStatement *compound;
	};
} Function;

Error function_parse(Function *out, TokenIterator *iter);
void function_free(Function *function);

#endif
