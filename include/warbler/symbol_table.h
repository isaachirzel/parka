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

typedef enum ValidationStatus
{
	VALIDATION_NOT_YET,
	VALIDATION_VALID,
	VALIDATION_INVALID
} ValidationStatus;

typedef struct SymbolData
{
	char *symbol;
	usize index;
	SymbolType type;
	bool isValid;
	bool isDestroyed;
} SymbolData;

typedef struct SymbolTable
{
	SymbolData *globalSymbols;
	usize globalSymbolCount;
	usize globalSymbolCapacity;
	
	// Local symbols
	SymbolData *localSymbols;
	usize localSymbolCount;
	usize localSymbolCapacity;

	// Packages
	Scope scope;

	// Blocks
	usize *blocks;
	usize blockCount;
	usize blockCapacity;

	// Context
	ProgramContext *context;
	const ProgramSyntax *syntax;
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
SymbolData *symbolTableAddGlobal(SymbolTable *table, const char *symbol);
SymbolData *symbolTableAddLocal(SymbolTable *table, const char *symbol);
usize symbolTableAddFunction(SymbolTable *table, const FunctionContext *context);
usize symbolTableAddStruct(SymbolTable *table, const StructContext *context);
usize symbolTableAddVariable(SymbolTable *table, const VariableContext *context);
usize symbolTableAddParameter(SymbolTable *table, const ParameterContext *context);
void symbolTablePushBlock(SymbolTable *table);
void symbolTablePopBlock(SymbolTable *table);
void symbolTableSetScopeFromSymbol(SymbolTable *table, const char *symbol);
const char *getSymbolTypeName(SymbolType type);
const char *symbolTableGetSymbol(AnnotationType type, usize index);

void symbolDataValidate(SymbolData *symbol, usize index);
void symbolDataInvalidate(SymbolData *symbol);
void symbolDataDestroy(SymbolData *symbol);
void symbolDataReinitialize(SymbolData *symol);

const StructContext *programStructAt(const ProgramContext *program, usize index);
const FunctionContext *programFunctionAt(const ProgramContext *program, usize index);
const VariableContext *programVariableAt(const ProgramContext *program, usize index);
const ParameterContext *programParameterAt(const ProgramContext *program, usize index);

const StructContext *tableStructAt(const SymbolTable *table, usize index);
const FunctionContext *tableFunctionAt(const SymbolTable *table, usize index);
const VariableContext *tableVariableAt(const SymbolTable *table, usize index);
const ParameterContext *tableParameterAt(const SymbolTable *table, usize index);

const PrimitiveContext *primitiveAt(usize index);

#define structAt(obj, index) (_Generic((obj), const ProgramContext *: programStructAt, const SymbolTable *: tableStructAt)(obj, index))
#define functionAt(obj, index) (_Generic((obj), const ProgramContext *: programFunctionAt, const SymbolTable *: tableFunctionAt)(obj, index))
#define parameterAt(obj, index) (_Generic((obj), const ProgramContext *: programParameterAt, const SymbolTable *: tableParameterAt)(obj, index))
#define variableAt(obj, index) (_Generic((obj), const ProgramContext *: programVariableAt, const SymbolTable *: tableVariableAt)(obj, index))

#endif
