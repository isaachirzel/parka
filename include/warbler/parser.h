#ifndef WARBLER_PARSER_H
#define WARBLER_PARSER_H

#include <warbler/ast.h>
#include <warbler/util/project.h>

bool parseExpression(Expression *out, Token *token);
bool parseStatement(Statement *out, Token *token);
bool parse(const Project *project);

#endif
