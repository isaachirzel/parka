#ifndef PARKA_AST_VARIABLE_H
#define PARKA_AST_VARIABLE_H

#include "parka/ast/type.h"
#include "parka/symbol_table.h"

typedef struct Variable
{
	Token name;
	char *symbol;
	TypeAnnotation annotation;
	bool isMutable;
	bool isExplicitlyTyped;
} Variable;

bool parseVariable(Variable *out, Token *token);
bool validateVariable(Variable *node, LocalSymbolTable *localTable);
void variableFree(Variable *node);

#endif
