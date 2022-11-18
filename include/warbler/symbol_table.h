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

void symbolTableInitialize();
void symbolTableDestroy();

SymbolId symbolTableAddPackage();
SymbolId symbolTableAddStruct();
SymbolId symbolTableAddFunction();
SymbolId symbolTableAddVariable();
SymbolId symbolTableAddParameter();

bool symbolTableDeclareGlobal(const SymbolId *id);
bool symbolTableDeclareLocal(const SymbolId *id);

SymbolId *symbolTableResolve(const char *identifier);
SymbolId *symbolTableFind(const char *symbol);
SymbolId *symbolTableFindGlobal(const char *symbol);
SymbolId *symbolTableFindLocal(const char *symbol);
char *symbolTableCreateSymbol(const char *identifier);
char *symbolTableCreateTokenSymbol(const Token *token);

void symbolTablePushBlock();
void symbolTablePopBlock();

void symbolTableSetScopeFromSymbol(const char *symbol);
const char *symbolTypeGetName(SymbolType type);

const char *symbolTableGetSymbol(const SymbolId *id);

usize symbolTablePackageCount();

Package *symbolTableGetPackage(const SymbolId *id);
Variable *symbolTableGetVariable(const SymbolId *id);
Parameter *symbolTableGetParameter(const SymbolId *id);
Function *symbolTableGetFunction(const SymbolId *id);
Struct *symbolTableGetStruct(const SymbolId *id);
const Primitive *symbolTableGetPrimitive(const SymbolId *id);

#endif
