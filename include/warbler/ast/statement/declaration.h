#ifndef WARBLER_AST_STATEMENT_DECLARATION_H
#define WARBLER_AST_STATEMENT_DECLARATION_H

#include "warbler/ast/expression/expression.h"
#include "warbler/util/primitives.h"

typedef struct Declaration
{
	usize variableId;
	Expression value;
} Declaration;

bool parseDeclaration(Declaration *node, Token *token);
bool validateDeclaration(Declaration *node, LocalSymbolTable *localTable);
void declarationFree(Declaration *node);

#endif
