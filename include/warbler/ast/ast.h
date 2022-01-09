#ifndef WARBLER_PARSER_H
#define WARBLER_PARSER_H

// local headers
#include <warbler/ast/program.h>
#include <warbler/token_array.h>

typedef struct Ast
{
	Program program;
} Ast;

Error ast_parse(Ast *out, TokenArray *tokens);
void ast_free(Ast *ast);

#endif
