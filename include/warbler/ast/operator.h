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
	bool isConst;
	// SelfType { Value, Ref, Const Ref }
	bool isBinary; // Used to determin if rightType is used
} Operator;

typedef Array(Operator) OperatorList;

typedef struct Operators
{
	OperatorList adds;
} Operators;

Operators operatorsCreate(void);

#endif
