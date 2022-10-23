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
#include <assert.h>

typedef enum ValidationStatus
{
	VALIDATION_NOT_YET,
	VALIDATION_VALID,
	VALIDATION_INVALID
} ValidationStatus;

typedef struct SymbolData
{
	union
	{
		const StructSyntax *structSyntax;
		const FunctionSyntax *functionSyntax;
		const VariableSyntax *variableSyntax;
		const ParameterSyntax *parameterSyntax;
	};

	char *symbol;
	usize index;
	SymbolType type;
	ValidationStatus status;
	bool isDestroyed;
} SymbolData;

typedef struct SymbolTable
{
	SymbolData *globalSymbols;
	usize globalSymbolCount;
	SymbolData *localSymbols;
	usize localSymbolCount;
	usize localSymbolCapacity;
	char **packages;
	usize packageCount;

	StructContext *structs;
	FunctionContext *functions;
	VariableContext *variables;
	ParameterContext *parameters;
	usize structCount;
	usize functionCount;
	usize variableCount;
	usize parameterCount;
} SymbolTable;

typedef struct AddSymbolResult
{
	bool success;
	SymbolData *data;
} AddSymbolResult;

SymbolData *symbolTableFind(SymbolTable *table, const char *symbol);
SymbolData *symbolTableFindGlobal(SymbolTable *table, const char *symbol);
SymbolData *symbolTableFindLocal(SymbolTable *table, const char *symbol);
void popSymbols(SymbolTable *table, usize index);
char *generateSymbol(const SymbolTable *table, AnnotationType type, usize index);
const char *getSymbolTypeName(SymbolType type);
bool addGlobalSymbols(SymbolTable *table, const ProgramSyntax *syntax);

AddSymbolResult symbolTableAddGlobal(SymbolTable *table, SymbolData *data);
AddSymbolResult symbolTableAddLocal(SymbolTable *table, SymbolData *data);
AddSymbolResult symbolTableAddFunction(SymbolTable *table, const FunctionSyntax *syntax);
AddSymbolResult symbolTableAddStruct(SymbolTable *table, const StructSyntax *syntax);
AddSymbolResult symbolTableAddVariable(SymbolTable *table, const VariableSyntax *syntax);
AddSymbolResult symbolTableAddParameter(SymbolTable *table, const ParameterSyntax *syntax);

void symbolTableValidateVariable(SymbolTable *table, SymbolData *data, VariableContext *context);
void symbolTableValidateParameter(SymbolTable *table, SymbolData *data, ParameterContext *context);
void symbolTableValidateStruct(SymbolTable *table, SymbolData *data, StructContext *context);
void symbolTableValidateFunction(SymbolTable *table, SymbolData *data, FunctionContext *context);

bool symbolTableFromProgramSyntax(SymbolTable *out, const ProgramSyntax *program);
void symbolTableSetPackagesFromSymbol(SymbolTable *table, char *symbol);
char *symbolTableGetSymbol(AnnotationType type, usize index);

static inline SymbolData createPackageSymbol(const char *symbol)
{
	SymbolData data =
	{
		.symbol = duplicateString(symbol),
		.type = SYMBOL_PACKAGE,
		.status = VALIDATION_VALID
	};

	return data;
}

void symbolDataValidate(SymbolData *symbol, usize index);
void symbolDataInvalidate(SymbolData *symbol);
void symbolDataDestroy(SymbolData *symbol);
void symbolDataReinitialize(SymbolData *symol);

static inline bool isSymbolValiated(SymbolData *symbol) { return symbol->status == VALIDATION_VALID; }
static inline bool isSymbolInvalid(SymbolData *symbol) { return symbol->status == VALIDATION_INVALID; }
static inline bool isSymbolNotYetValidated(SymbolData *symbol) { return symbol->status == VALIDATION_NOT_YET; }

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
