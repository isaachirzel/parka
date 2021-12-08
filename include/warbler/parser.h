#ifndef WARBLER_PARSER_H
#define WARBLER_PARSER_H

// local
#include <warbler/ast.h>
#include <warbler/error.h>
#include <warbler/token.h>

// external
#include <hirzel/array.h>

Error parse_program(Program **out, const Token **tokens);
Error parse_module(Module **out, const Token **tokens);
Error parse_function(Function **out, const Token **tokens);
Error parse_statemnt(Statement **out, const Token **tokens);
Error parse_identifier(Identifier **out, const Token **tokens);

#endif
