#ifndef PARKA_AST_EXPRESSION_CALL_H
#define PARKA_AST_EXPRESSION_CALL_H

#include "parka/ast/expression/expression.h"
#include "parka/symbol_table.h"

typedef struct CallExpression
{
	Expression *expressions;
	usize count;
} CallExpression;

bool parseCallExpression(CallExpression* out, Token *token);
bool validateCallExpression(CallExpression *node, LocalSymbolTable *localTable);
void callExpressionFree(CallExpression *node);

#endif
