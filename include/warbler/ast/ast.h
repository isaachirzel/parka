#ifndef WARBLER_PARSER_H
#define WARBLER_PARSER_H

// local headers
#include <warbler/ast/program.h>

// external headers
#include <hirzel/array.h>

typedef struct Ast
{
	Program program;
} Ast;

Error ast_parse(Ast *out, HxArray *tokens);
void ast_free(Ast *ast);

#endif
