#ifndef WARBLER_PARSER_HPP
#define WARBLER_PARSER_HPP

// local headers
#include <warbler/ast/program.hpp>
#include <warbler/token.hpp>

namespace warbler
{
typedef struct Ast
{
	Program program;
} Ast;

Error ast_parse(Ast *out, const std::vector<Token>& tokens);
void ast_free(Ast *ast);
}
#endif
