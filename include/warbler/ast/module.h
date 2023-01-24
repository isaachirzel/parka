#ifndef WARBLER_AST_MODULE_H
#define WARBLER_AST_MODULE_H

#include "warbler/scope.h"
#include "warbler/util/array.h"
#include "warbler/util/file.h"

typedef struct Module
{
	char *symbol;
	IndexList functionIds;
	IndexList structIds;
} Module;

typedef Array(Module) ModuleList;

bool parseModule(Module *node, const File *file, const char *package);
bool declareModule(Module *module);
bool validateModule(Module *module, const Scope *packageScope);
void moduleFree(Module *node);

#endif