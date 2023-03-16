#ifndef PARKA_SYMBOL_H
#define PARKA_SYMBOL_H

#include "parka/token.h"
typedef enum SymbolType
{
	SYMBOL_PACKAGE,
	SYMBOL_STRUCT,
	SYMBOL_PRIMITIVE,
	SYMBOL_FUNCTION,
	SYMBOL_VARIABLE,
	SYMBOL_PARAMETER
} SymbolType;

char *createSymbol(const char *package, const Token *name);
const char *symbolTypeName(SymbolType type);

#endif
