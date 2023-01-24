#ifndef WARBLER_AST_EXPRESSION_PREFIX_H
#define WARBLER_AST_EXPRESSION_PREFIX_H

#include "warbler/ast/expression/expression.h"
#include "warbler/token.h"

typedef enum PrefixType
{
	PREFIX_REFERENCE,
	PREFIX_DEREFERENCE,
	PREFIX_POSITIVE,
	PREFIX_NEGATIVE,
	PREFIX_BITWISE_NOT,
	PREFIX_BOOLEAN_NOT
} PrefixType;

typedef struct Prefix
{
	Token token;
	Expression expression;
	PrefixType type;
} Prefix;

bool parsePrefix(Expression *out, Token *token);
bool validatePrefix(Prefix *node, LocalSymbolTable *localTable);
void prefixFree(Prefix *node);

#endif
