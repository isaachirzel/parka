#ifndef PARKA_AST_MODULE_H
#define PARKA_AST_MODULE_H

#include "parka/scope.h"
#include "parka/util/array.h"
#include "parka/util/file.h"

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