#ifndef PARKA_AST_PARAMETER_H
#define PARKA_AST_PARAMETER_H

#include "parka/ast/type.h"
#include "parka/symbol_table.h"
#include "parka/util/array.h"

typedef struct Parameter
{
	Token name;
	char *symbol;
	TypeAnnotation annotation;
	bool isMutable;
} Parameter;

bool parseParameter(Parameter *out, Token *token);
bool parseParameterList(IndexList *out, Token *token);
bool validateParameter(Parameter *node, LocalSymbolTable *localTable);
bool validateParameterList(const IndexList *ids, LocalSymbolTable *localTable);
bool parseFunction(usize *out, Token *token, const char *package);
void parameterFree(Parameter *node);

#endif
