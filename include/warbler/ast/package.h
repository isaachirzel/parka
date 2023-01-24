#ifndef WARBLER_AST_PACKAGE_H
#define WARBLER_AST_PACKAGE_H

#include "warbler/ast/module.h"
#include "warbler/scope.h"
#include "warbler/util/directory.h"

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
