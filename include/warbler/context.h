#ifndef WARBLER_CONTEXT_H
#define WARBLER_CONTEXT_H

#include "warbler/ast.h"
#include "warbler/scope.h"
#include "warbler/util/primitives.h"

typedef struct BlockContext
{
	usize index;
	Block *node;
} BlockContext;

typedef struct FunctionContext
{
	Function *node;
	BlockContext *blocks;
	usize blockCount;
	usize blockCapacity;
} FunctionContext;

typedef struct PackageContext
{
	Package *node;
	Scope scope;
} PackageContext;

typedef struct ValidationContext
{
	PackageContext *package;
	FunctionContext *function;
} ValidationContext;

FunctionContext functionContextCreate(Function *node);
void functionContextFree(FunctionContext *context);

PackageContext packageContextCreate(Package *node);
void packageContextFree(PackageContext *context);

ValidationContext validationContextCreate(PackageContext *package);

#endif
