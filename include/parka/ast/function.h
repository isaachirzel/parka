#ifndef PARKA_AST_FUNCTION_H
#define PARKA_AST_FUNCTION_H

#include "parka/ast/expression/expression.h"
#include "parka/ast/operator.h"
#include "parka/util/array.h"

typedef struct Function
{
	Token name;
	char *symbol;
	IndexList parameterIds;
	TypeAnnotation returnType;
	Expression body;
	Operators operators;
	bool hasReturnType;
} Function;

bool parseFunction(usize *out, Token *token, const char *package);
bool validateFunction(Function *node, LocalSymbolTable *localTable);
void functionFree(Function *node);
const Type *functionGetReturnType(const Function *function);

#endif
