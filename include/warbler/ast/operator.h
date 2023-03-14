#ifndef WARBLER_AST_OPERATOR_H
#define WARBLER_AST_OPERATOR_H

#include "warbler/ast/expression/expression.h"
#include "warbler/ast/type.h"
#include "warbler/util/array.h"

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
