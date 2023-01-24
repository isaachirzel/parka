#ifndef WARBLER_SYMBOL_TABLE_H
#define WARBLER_SYMBOL_TABLE_H

#include "warbler/symbol.h"
#include "warbler/util/array.h"
#include "warbler/util/string.h"
#include "warbler/util/table.h"
#include "warbler/util/primitives.h"
#include "warbler/util/memory.h"
#include "warbler/scope.h"

#include <assert.h>

struct Function;
struct Package;
struct Parameter;
struct Primitive;
struct Variable;
struct Struct;

typedef enum ValidationStatus
{
	VALIDATION_PENDING,
	VALIDATION_INVALID,
	VALIDATION_VALID
} ValidationStatus;

typedef struct Symbol
{
	char *key;
	usize index;
	SymbolType type;
	ValidationStatus status;
} Symbol;

typedef struct BlockInfo
{
	struct Block *node;
	usize offset;
} BlockInfo;

typedef struct LocalSymbolTable
{
	Symbol *symbols;
	usize symbolCount;
	usize symbolCapacity;

	BlockInfo *blocks;
	usize blockCount;
	usize blockCapacity;

	struct Function *function;
	const Scope *packageScope;
} LocalSymbolTable;

typedef bool (*EntityAction)(usize);
typedef bool (*SymbolAction)(Symbol *symbol);

void symbolTableInitialize(const char *projectName);
void symbolTableDestroy(void);

usize symbolTableAddPackage(void);
usize symbolTableAddStruct(void);
usize symbolTableAddFunction(void);
usize symbolTableAddVariable(void);
usize symbolTableAddParameter(void);

bool symbolTableDeclareGlobal(SymbolType type, usize index);
bool symbolTableDeclareLocal(LocalSymbolTable *localTable, SymbolType type, usize index);

Symbol *symbolTableResolve(LocalSymbolTable *localTable, const Token *token);
Symbol *symbolTableResolveGlobal(const Scope *scope, const Token *token);

void symbolTableSetScopeFromSymbol(const char *symbol);
Symbol *symbolTableGetSymbol(usize index);
const char *symbolTypeGetName(SymbolType type);
const Token *symbolTableGetToken(usize symbolIndex);
const char *symbolGetKey(SymbolType type, usize index);

bool symbolTableForEachEntity(SymbolType type, EntityAction action);

struct Package *symbolTableGetPackage(usize index);
struct Variable *symbolTableGetVariable(usize index);
struct Parameter *symbolTableGetParameter(usize index);
struct Function *symbolTableGetFunction(usize index);
struct Struct *symbolTableGetStruct(usize index);
const struct Primitive *symbolTableGetPrimitive(usize index);

LocalSymbolTable localSymbolTableCreate(const Scope *packageScope);
void localSymbolTableDestroy(LocalSymbolTable *localTable);
void localSymbolTableClear(LocalSymbolTable *localTable);
void localSymbolTablePushBlock(LocalSymbolTable *localTable, struct Block *block);
struct Block *localSymbolTableGetCurrentBlock(LocalSymbolTable *localTable);
void localSymbolTablePopBlock(LocalSymbolTable *localTable);

#endif
