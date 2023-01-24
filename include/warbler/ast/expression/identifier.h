#ifndef WARBLER_AST_EXPRESSION_IDENTIFIER_H
#define WARBLER_AST_EXPRESSION_IDENTIFIER_H

#include "warbler/ast/type.h"
#include "warbler/symbol.h"
#include "warbler/symbol_table.h"
#include "warbler/token.h"

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
