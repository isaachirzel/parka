#ifndef WARBLER_SYMBOL_TABLE_H
#define WARBLER_SYMBOL_TABLE_H

#include <warbler/util/array.h>
#include <warbler/util/string.h>
#include <warbler/util/table.h>
#include <warbler/util/primitives.h>
#include <warbler/type.h>
#include <warbler/util/memory.h>
#include <warbler/syntax.h>
#include <warbler/context.h>
#include <warbler/scope.h>
#include <assert.h>

typedef struct SymbolData
{
	char *symbol;
	SymbolId id;
	bool isValid;
	bool isDefined;
	Token name;
} SymbolData;

typedef struct SymbolTable
{
	// Globals
	SymbolData *globals;
	usize globalCount;
	usize globalCapacity;

	// Locals
	SymbolData *locals;
	usize localCount;
	usize localCapacity;
	
	usize *blocks;
	usize blockCount;
	usize blockCapacity;

	usize packageIndex;
	usize moduleIndex;
	usize globalIndex;
	usize localIndex;

	Scope package;

	ProgramContext *program;
} SymbolTable;

SymbolTable symbolTableCreate(ProgramContext *context, const ProgramSyntax *syntax);
void symbolTableDestroy(SymbolTable *table);
SymbolData *symbolTableResolve(SymbolTable *table, const char *identifier);
SymbolData *symbolTableFind(SymbolTable *table, const char *symbol);
SymbolData *symbolTableFindGlobal(SymbolTable *table, const char *symbol);
SymbolData *symbolTableFindFunctionLocal(SymbolTable *table, const char *symbol);
void popSymbols(SymbolTable *table, usize index);
char *generateSymbol(const SymbolTable *table, AnnotationType type, usize index);
char *symbolTableCreateSymbol(SymbolTable *table, const char *identifier);

SymbolData *symbolTableDeclareGlobal(SymbolTable *table, const char *symbol);
SymbolData *symbolTableDeclareLocal(SymbolTable *table, const Token *name);

void symbolTablePushBlock(SymbolTable *table);
void symbolTablePopBlock(SymbolTable *table);
void symbolTableSetScopeFromSymbol(SymbolTable *table, const char *symbol);
const char *getSymbolTypeName(SymbolType type);
const char *symbolTableGetSymbol(AnnotationType type, usize index);

void symbolDataValidate(SymbolData *symbol, usize index);
void symbolDataInvalidate(SymbolData *symbol);
void symbolDataDestroy(SymbolData *symbol);
void symbolDataReinitialize(SymbolData *symol);

const PrimitiveContext *primitiveAt(usize index);

#endif
