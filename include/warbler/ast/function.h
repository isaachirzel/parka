#ifndef WARBLER_AST_FUNCTION_H
#define WARBLER_AST_FUNCTION_H

#include "warbler/ast/expression.h"
#include "warbler/symbol_id.h"

typedef struct Function
{
	Token name;
	char *symbol;
	IdList parameterIds;
	TypeAnnotation returnType;
	Expression body;
	bool hasReturnType;
} Function;

typedef struct Parameter
{
	Token name;
	char *symbol;
	TypeAnnotation annotation;
	bool isMutable;
} Parameter;

void functionFree(Function *node);
void parameterFree(Parameter *node);
const Type *functionGetReturnType(const Function *function);

#endif
