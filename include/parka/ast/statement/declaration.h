#ifndef PARKA_AST_STATEMENT_DECLARATION_H
#define PARKA_AST_STATEMENT_DECLARATION_H

#include "parka/ast/expression/expression.h"
#include "parka/util/primitives.h"

typedef struct Declaration
{
	usize variableId;
	Expression value;
} Declaration;

bool parseDeclaration(Declaration *node, Token *token);
bool validateDeclaration(Declaration *node, LocalSymbolTable *localTable);
void declarationFree(Declaration *node);

#endif
