#ifndef WARBLER_SYMBOL_H
#define WARBLER_SYMBOL_H

typedef enum SymbolType
{
	SYMBOL_PACKAGE,
	SYMBOL_STRUCT,
	SYMBOL_PRIMITIVE,
	SYMBOL_FUNCTION,
	SYMBOL_VARIABLE,
	SYMBOL_PARAMETER
} SymbolType;

const char *symbolTypeName(SymbolType type);

#endif
