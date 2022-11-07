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

typedef struct Validation
{
	union
	{
		const StructSyntax *structSyntax;
		const FunctionSyntax *functionSyntax;
	};

	SymbolId id;
} Validation;

void symbolTableInitialize();
ProgramContext symbolTableExport();
void symbolTableDestroy();

SymbolId *symbolTableDeclarePackage(const char *symbol);
SymbolId *symbolTableDeclareStruct(const StructSyntax *syntax);
SymbolId *symbolTableDeclareFunction(const FunctionSyntax *syntax);
SymbolId *symbolTableDeclareVariable(const VariableSyntax *syntax);
SymbolId *symbolTableDeclareParameter(const ParameterSyntax *syntax);

SymbolId *symbolTableResolve(const char *identifier);
SymbolId *symbolTableFind(const char *symbol);
SymbolId *symbolTableFindGlobal(const char *symbol);
SymbolId *symbolTableFindLocal(const char *symbol);
char *symbolTableCreateSymbol(const char *identifier);

void symbolTablePushBlock();
void symbolTablePopBlock();

void symbolTableSetScopeFromSymbol(const char *symbol);
const char *symbolTypeGetName(SymbolType type);

const char *symbolTableGetSymbol(SymbolId *id);

usize symbolTableGetValidationCount();
const Validation *symbolTableValidationAt(usize index);
VariableContext *symbolTableVariableAt(usize index);
ParameterContext *symbolTableParameterAt(usize index);
FunctionContext *symbolTableFunctionAt(usize index);
StructContext *symbolTableStructAt(usize index);
const PrimitiveContext *symbolTablePrimitiveAt(usize index);

#endif
