#ifndef WARBLER_AST_EXPRESSION_CALL_H
#define WARBLER_AST_EXPRESSION_CALL_H

#include "warbler/ast/expression/expression.h"
#include "warbler/symbol_table.h"

typedef struct CallExpression
{
	Expression *expressions;
	usize count;
} CallExpression;

bool parseCallExpression(CallExpression* out, Token *token);
bool validateCallExpression(CallExpression *node, LocalSymbolTable *localTable);
void callExpressionFree(CallExpression *node);

#endif
