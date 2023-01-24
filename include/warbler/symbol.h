#ifndef WARBLER_SYMBOL_H
#define WARBLER_SYMBOL_H

#include "warbler/token.h"
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
