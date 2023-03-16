#ifndef PARKA_AST_EXPRESSION_MULTIPLICATIVE_H
#define PARKA_AST_EXPRESSION_MULTIPLICATIVE_H

#include "parka/ast/expression/expression.h"

typedef enum MultiplicativeType
{
	MULTIPLICATIVE_MULTIPLY,
	MULTIPLICATIVE_DIVIDE,
	MULTIPLICATIVE_MODULUS
} MultiplicativeType;

typedef struct MultiplicativeRhs
{
	Expression expr;
	MultiplicativeType type;
} MultiplicativeRhs;

typedef struct MultiplicativeExpression
{
	Expression lhs;
	MultiplicativeRhs* rhs;
	usize rhsCount;
} MultiplicativeExpression;

bool parseMultiplicativeExpression(Expression *out, Token *token);
bool validateMultiplicativeExpression(MultiplicativeExpression *node, LocalSymbolTable *localTable);
void multiplicativeExpressionFree(MultiplicativeExpression *node);

#endif
