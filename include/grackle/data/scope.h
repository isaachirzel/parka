#ifndef SCOPE_H
#define SCOPE_H

// local includes
#include <grackle/container/symtbl.h>


typedef struct scope
{
	symbol_t *sym;
	symtbl_t *sym_table;
} scope_t;

#endif