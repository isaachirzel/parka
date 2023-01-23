#ifndef WARBLER_AST_OPERATOR_H
#define WARBLER_AST_OPERATOR_H

#include "warbler/ast/type.h"
#include "warbler/util/array.h"

typedef enum OperatorType
{
	OPERATOR_PLUS
} OperatorType;

typedef struct Operator
{
	OperatorType type;
	Type rightType;
	Type returnType;
	bool isSelfConst;
	bool isBinary;
} Operator;

typedef struct Operators
{
	Array(Operator) adds;
} Operators;

Operators operatorsCreate(void);

#endif
