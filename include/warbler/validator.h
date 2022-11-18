#ifndef WARBLER_VALIDATOR_H
#define WARBLER_VALIDATOR_H

#include <warbler/ast.h>
#include <warbler/ast.h>
#include <warbler/symbol_table.h>

bool validateStatement(Statement *node);
bool validateExpression(Expression *node);
bool validate();

#endif
