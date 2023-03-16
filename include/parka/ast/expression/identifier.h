#ifndef PARKA_AST_EXPRESSION_IDENTIFIER_H
#define PARKA_AST_EXPRESSION_IDENTIFIER_H

#include "parka/ast/type.h"
#include "parka/symbol.h"
#include "parka/symbol_table.h"
#include "parka/token.h"

typedef struct Identifier
{
	Token token;
	usize index;
	SymbolType type;
} Identifier;

bool parseIdentifier(struct Expression *out, Token *token);
bool validateIdentifier(Identifier *node, LocalSymbolTable *localTable);
bool identifierGetType(Type *out, Identifier *node, const Type *expected);

#endif
