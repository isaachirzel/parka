#ifndef WARBLER_AST_H
#define WARBLER_AST_H

#include "warbler/util/array.h"

typedef struct Module
{
	char *symbol;
	IndexList functionIds;
	IndexList structIds;
} Module;

typedef struct Package
{
	char *symbol;
	Array(Module) modules;
} Package;

void moduleFree(Module *node);
void packageFree(Package *node);

#endif
