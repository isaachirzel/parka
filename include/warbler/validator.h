#ifndef WARBLER_VALIDATOR_H
#define WARBLER_VALIDATOR_H

#include <warbler/syntax.h>
#include <warbler/context.h>
#include <warbler/symbol_table.h>

typedef struct ContainingTypes
{
    char **names;
    usize count;
    usize capacity;
} ContainingTypes;

bool validateStatement(StatementContext *out, const StatementSyntax *syntax, SymbolTable *symbols);
bool validateStruct(StructContext *out, const StructSyntax *syntax, SymbolTable *symbols, ContainingTypes *containingTypes);
bool validateExpression(ExpressionContext *out, const ExpressionSyntax *syntax, SymbolTable *symbols);
bool validate(ProgramContext *out, const ProgramSyntax *syntax);

#endif
