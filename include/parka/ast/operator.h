#ifndef PARKA_AST_OPERATOR_H
#define PARKA_AST_OPERATOR_H

#include "parka/ast/expression/expression.h"
#include "parka/ast/type.h"
#include "parka/util/array.h"

typedef enum OperatorType
{
	OPERATOR_ADD
} OperatorType;

typedef struct Operator
{
	OperatorType type;
	Type rightType;
	Type returnType;
	bool isBuiltIn;
	Expression body;
} Operator;

typedef Array(Operator) OperatorList;

typedef struct Operators
{
	OperatorList addOperators;
} Operators;

Operators operatorsCreate(void);
usize operatorsAddBuiltIn(Operators *operators, OperatorType type, Type *rightType, Type *returnType);

bool operatorIsBinary(const Operator *operator);
bool parseOperator(Operators *operators, Token *token);

#endif
