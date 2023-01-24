#ifndef WARBLER_AST_FUNCTION_H
#define WARBLER_AST_FUNCTION_H

#include "warbler/ast/expression/expression.h"
#include "warbler/ast/operator.h"
#include "warbler/util/array.h"

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
