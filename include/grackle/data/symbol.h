#ifndef SYMBOL_H
#define SYMBOL_H

// local includes
#include <grackle/data/string.h>

enum SymbolType
{
	SYM_GLOBAL,
	SYM_FUNCTION,
	SYM_VARIABLE,
	SYM_ANONYMOUS,
};

typedef struct symbol
{
	string_t *str;
	char type;
} symbol_t;

#endif
