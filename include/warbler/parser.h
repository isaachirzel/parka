#ifndef WARBLER_PARSER_H
#define WARBLER_PARSER_H

// local
#include <warbler/ast.h>
#include <warbler/error.h>
#include <warbler/token.h>

// external
#include <hirzel/array.h>

Error parse_program(Program **out, const Token **iterator);
Error parse_module(Module **out, const Token **iterator);
Error parse_function(Function **out, const Token **iterator);
Error parse_statemnt(Statement **out, const Token **iterator);

Error parse_identifier(Identifier **out, const Token **iterator);

// expressions
Error parse_expression(Expression **out, const Token **iterator);
Error parse_assignment_expression(AssignmentExpression **out, const Token **iterator);

#endif
