#ifndef WARBLER_SYMBOL_TABLE_H
#define WARBLER_SYMBOL_TABLE_H

#include <warbler/util/array.h>
#include <warbler/util/string.h>
#include <warbler/util/table.h>
#include <warbler/util/primitives.h>
#include <warbler/type.h>
#include <warbler/util/memory.h>
#include <warbler/scope.h>
#include <warbler/ast.h>
#include <assert.h>

typedef enum ValidationStatus
{
	VALIDATION_PENDING,
	VALIDATION_INVALID,
	VALIDATION_VALID
} ValidationStatus;

typedef struct SymbolData
{
	char *symbol;
	SymbolId id;
	ValidationStatus status;
} SymbolData;

typedef bool (*SymbolDataAction)(SymbolData *data);

void symbolTableInitialize(const char *projectName);
void symbolTableDestroy();

SymbolId symbolTableAddPackage();
SymbolId symbolTableAddStruct();
SymbolId symbolTableAddFunction();
SymbolId symbolTableAddVariable();
SymbolId symbolTableAddParameter();

bool symbolTableDeclareGlobal(const SymbolId *id);
bool symbolTableDeclareLocal(const SymbolId *id);

SymbolData *symbolTableResolve(const Token *token);
char *symbolTableCreateSymbol(const char *identifier);
char *symbolTableCreateTokenSymbol(const Token *token);

void symbolTablePushBlock();
void symbolTablePopBlock();

void symbolTableSetScopeFromSymbol(const char *symbol);
const char *symbolTypeGetName(SymbolType type);
const char *symbolTableGetSymbol(const SymbolId *id);
const Token *symbolTableGetToken(const SymbolId *id);

bool symbolTableForEachEntity(SymbolType type, SymbolIdAction action);
bool symbolTableForEachGlobal(SymbolDataAction action);

Package *symbolTableGetPackage(const SymbolId *id);
Local *symbolTableGetVariable(const SymbolId *id);
Local *symbolTableGetParameter(const SymbolId *id);
Function *symbolTableGetFunction(const SymbolId *id);
Struct *symbolTableGetStruct(const SymbolId *id);
const Primitive *symbolTableGetPrimitive(const SymbolId *id);

#endif
