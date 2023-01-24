#ifndef WARBLER_AST_EXPRESSION_POSTFIX_H
#define WARBLER_AST_EXPRESSION_POSTFIX_H

#include "warbler/ast/expression/call.h"
#include "warbler/ast/expression/expression.h"

typedef enum PostfixType
{
	POSTFIX_INDEX,
	POSTFIX_FUNCTION_CALL,
	POSTFIX_MEMBER
} PostfixType;

typedef struct Postfix
{
	Expression expression;
	union
	{
		Expression index;
		CallExpression call;
		Token member;
	};
	PostfixType type;
} Postfix;

bool parsePostfix(Expression *out, Token *token);
bool validatePostfix(Postfix *node, LocalSymbolTable *localTable);
void postfixFree(Postfix *node);

#endif
