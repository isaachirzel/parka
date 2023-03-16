#ifndef PARKA_AST_PACKAGE_H
#define PARKA_AST_PACKAGE_H

#include "parka/ast/module.h"
#include "parka/scope.h"
#include "parka/util/directory.h"

typedef struct Package
{
	char *symbol;
	ModuleList modules;
} Package;

bool parsePackage(const Directory *directory, Scope *scope, const char *name);
bool declarePackage(usize index);
bool validatePackage(usize index);
void packageFree(Package *node);

#endif
