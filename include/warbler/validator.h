#ifndef WARBLER_VALIDATOR_H
#define WARBLER_VALIDATOR_H

#include <warbler/syntax.h>
#include <warbler/context.h>
#include <warbler/symbol_table.h>

bool validateStatement(StatementContext *out, const StatementSyntax *syntax, SymbolTable *symbols);
bool validateExpression(ExpressionContext *out, const ExpressionSyntax *syntax, SymbolTable *symbols);
bool validate(ProgramContext *out, const ProgramSyntax *syntax);

#endif
