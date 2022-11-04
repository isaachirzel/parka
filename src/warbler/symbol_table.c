#include <warbler/symbol_table.h>
#include <warbler/context.h>
#include <warbler/util/array.h>
#include <warbler/syntax.h>
#include <warbler/util/print.h>
#include <warbler/util/memory.h>

#include <string.h>

const char *getSymbolTypeName(SymbolType type)
{
	switch (type)
	{
		case SYMBOL_PACKAGE:
			return "package";

		case SYMBOL_STRUCT:
			return "struct";

		case SYMBOL_PRIMITIVE:
			return "primitive";

		case SYMBOL_FUNCTION:
			return "function";

		case SYMBOL_VARIABLE:
			return "variable";

		case SYMBOL_PARAMETER:
			return "parameter";

		default:
			exitWithError("Invalid SymbolType for type name: %d", type);
	}
}

SymbolData *symbolTableFindGlobal(SymbolTable *table, const char *symbol)
{
	for (usize i = 0; i < table->globalSymbolCount; ++i)
	{
		SymbolData *data = table->globalSymbols + i;

		if (!strcmp(symbol, data->symbol))
			return data;
	}

	return NULL;
}

static SymbolData *symbolTableFindLocalFromIndex(SymbolTable *table, usize index, const char *symbol)
{
	if (table->localSymbolCount == 0)
		return NULL;

	usize i = table->localSymbolCount - 1;

	while (true)
	{
		SymbolData *data = table->localSymbols + i;

		if (!strcmp(symbol, data->symbol))
			return data;

		if (i == index)
			break;

		i -= 1;
	}

	return NULL;
}

static inline usize symbolTableGetCurrentBlockIndex(SymbolTable *table)
{
	if (table->blockCount == 0)
		return 0;

	usize index = table->blocks[table->blockCount - 1];

	return index;
}

SymbolData *symbolTableFindFunctionLocal(SymbolTable *table, const char *symbol)
{
	return symbolTableFindLocalFromIndex(table, 0, symbol);
}

SymbolData *symbolTableFindBlockLocal(SymbolTable *table, const char *symbol)
{
	usize blockIndex = symbolTableGetCurrentBlockIndex(table);

	return symbolTableFindLocalFromIndex(table, blockIndex, symbol);
}

SymbolData *symbolTableFind(SymbolTable *table, const char *symbol)
{
	SymbolData *functionSymbol = symbolTableFindFunctionLocal(table, symbol);

	if (functionSymbol)
		return functionSymbol;

	SymbolData *globalSymbol = symbolTableFindGlobal(table, symbol);

	return globalSymbol;
}

SymbolData *symbolTableAddLocal(SymbolTable *table, const char *symbol)
{
	SymbolData *previous = symbolTableFindBlockLocal(table, symbol);

	if (previous)
	{
		printError("'%s' is already declared in this block.", symbol);
		// printNote("Previous declaration here.");
		return NULL;
	}

	usize index = table->localSymbolCount;

	incrementArray(table->localSymbols, &table->localSymbolCount, &table->localSymbolCapacity);

	SymbolData *ptr = table->localSymbols + index;
}

static char *createSymbol(const Scope *scope, usize count, const char *identifier)
{
	String symbol;

	stringReserve(&symbol, 128);

	for (usize i = 0; i < count; ++i)
	{
		const char *package = scope->names[i];

		stringPush(&symbol, package);
		stringPush(&symbol, "::");
	}

	stringPush(&symbol, identifier);

	return symbol.data;
}

void symbolTableSetScope(const char *symbol)
{
	assert(symbol != NULL);

	// TODO: Clear current package

	String tmp;

	stringReserve(&tmp, 64);

	// split symbol by '::'
	for (const char *iter = symbol; *iter; ++iter)
	{
		if (*iter == ':')
		{
			assert(iter[1] == ':');
			// TODO: push currentPackage tmp
			stringClear(&tmp);
			++iter;
			continue;
		}

		stringPush(&tmp, *iter);
	}
}

const char *symbolTableGet(const SymbolTable *table, AnnotationType type, usize index)
{
	switch (type)
	{
		case ANNOTATION_STRUCT:
		{
			const StructContext *context = structAt(table, index);

			return context->symbol;
		}
		case ANNOTATION_PRIMITIVE:
		{
			const PrimitiveContext *context = primitiveAt(index);

			return context->symbol;
		}

		default:
			exitWithError("Invalid AnnotationType: %d", type);
	}
}

char *symbolTableGetSymbolForIdentifier(const SymbolTable *table, const char *identifier)
{
	return createSymbol(&table->scope, table->context->packageCount, identifier);
}

SymbolData *symbolTableResolve(SymbolTable *table, const char *identifier)
{
	ProgramContext *program = table->context;
	
	SymbolData *local = symbolTableFindFunctionLocal(table, identifier);

	if (local)
		return local;

	for (i32 i = (i32)program->packageCount; i >= 0; --i)
	{
		// TODO: Optimize with stack symbol
		char *symbol = createSymbol(&table->scope, i, identifier);

		SymbolData *iter = symbolTableFindGlobal(table, symbol);

		deallocate(symbol);

		if (iter)
			return iter;
	}

	return NULL;
}

SymbolData *symbolTableAddGlobal(SymbolTable *table, const char *symbol)
{
	SymbolData *previous = symbolTableFindGlobal(table, symbol);

	if (previous)
		return NULL;

	usize index = table->globalSymbolCount;

	resizeArray(table->globalSymbols, ++table->globalSymbolCount);

	SymbolData *ptr = table->globalSymbols + index;

	return ptr;
}

usize symbolTableAddStruct(SymbolTable *table, const StructContext *context)
{
	SymbolData *ptr = symbolTableAddGlobal(table, context->symbol);

	if (!ptr)
		return SIZE_MAX;

	ProgramContext *program = table->context;
	usize index = program->structCount;

	resizeArray(program->structs, ++program->structCount);

	program->structs[index] = *context;

	SymbolData data =
	{
		.symbol = duplicateString(context->symbol),
		.index = index,
		.type = SYMBOL_STRUCT,
		.isValid = true,
		.isDestroyed = false
	};

	return index;
}

usize symbolTableAddFunction(SymbolTable *table, const FunctionContext *context)
{
	SymbolData *ptr = symbolTableAddGlobal(table, context->symbol);

	if (!ptr)
		return SIZE_MAX;

	ProgramContext *program = table->context;
	usize index = program->functionCount;

	resizeArray(program->functions, ++program->functionCount);

	program->functions[index] = *context;

	*ptr = (SymbolData)
	{
		.symbol = duplicateString(context->symbol),
		.index = index,
		.type = SYMBOL_FUNCTION,
		.isValid = true,
		.isDestroyed = false
	};

	return index;
}

usize symbolTableAddParameter(SymbolTable *table, const ParameterContext *context)
{
	SymbolData *ptr = symbolTableAddLocal(table, context->name);

	if (!ptr)
		return SIZE_MAX;

	ProgramContext *program = table->context;
	usize index = program->parameterCount;

	resizeArray(program->parameters, ++program->parameterCount);

	program->parameters[index] = *context;

	*ptr = (SymbolData)
	{
		.symbol = duplicateString(context->name),
		.index = index,
		.type = SYMBOL_PARAMETER,
		.isValid = true,
		.isDestroyed = false
	};

	return index;
}

usize symbolTableAddVariable(SymbolTable *table, const VariableContext *context)
{
	SymbolData *ptr = symbolTableAddLocal(table, context->name);

	if (!ptr)
		return SIZE_MAX;

	ProgramContext *program = table->context;
	usize index = program->variableCount;

	resizeArray(program->variables, ++program->variableCount);

	program->variables[index] = *context;

	*ptr = (SymbolData)
	{
		.symbol = duplicateString(context->name),
		.index = index,
		.type = SYMBOL_VARIABLE,
		.isValid = true,
		.isDestroyed = false
	};

	return index;
}

static bool containsSemicolon(const char * const identifier)
{
	for (const char * restrict pos = identifier; *pos; ++pos)
	{
		if (*pos == ':')
			return true;
	}

	return false;
}

const StructContext *programStructAt(const ProgramContext *program, usize index)
{
	assert(index < program->structCount);
	return program->structs + index;
}

const FunctionContext *programFunctionAt(const ProgramContext *program, usize index)
{
	assert(index < program->functionCount);
	return program->functions + index;
}

const VariableContext *programVariableAt(const ProgramContext *program, usize index)
{
	assert(index < program->variableCount);
	return program->variables + index;
}

const ParameterContext *programParameterAt(const ProgramContext *program, usize index)
{
	assert(index < program->parameterCount);
	return program->parameters + index;
}

const StructContext *tableStructAt(const SymbolTable *table, usize index)
{
	return programStructAt(table->context, index);
}

const FunctionContext *tableFunctionAt(const SymbolTable *table, usize index)
{
	return programFunctionAt(table->context, index);
}

const VariableContext *tableVariableAt(const SymbolTable *table, usize index)
{
	return programVariableAt(table->context, index);
}

const ParameterContext *tableParameterAt(const SymbolTable *table, usize index)
{
	return programParameterAt(table->context, index);
}

char *symbolTableCreateSymbol(SymbolTable *table, const char *identifier)
{
	String symbol = { 0 };
	Scope *scope = &table->scope;

	for (usize i = 0; i < scope->count; ++i)
	{
		if (i > 0)
			stringPushCString(&symbol, "::");

		stringPushCString(&symbol, scope->names[i]);
	}

	return symbol.data;
}

void symbolTableSetScopeFromSymbol(SymbolTable *table, const char *symbol)
{
	table->scope.count = 0;

	static char buffer[256];
	usize size = 0;
	const char *iter = symbol;

	for (const char *iter = symbol; *iter; ++iter)
	{
		if (*iter == ':')
		{
			iter += 1;
			assert(*iter == ':');

			buffer[size] = 0;
			size = 0;

			scopePush(&table->scope, buffer);

			continue;
		}

		buffer[size++] = *iter;
	}
}

void symbolDataDestroy(SymbolData *data)
{
	deallocate(data->symbol);
}

SymbolTable symbolTableCreate(ProgramContext *context, const ProgramSyntax *syntax)
{
	SymbolTable table =
	{
		.context = context,
		.syntax = syntax,
		.globalSymbolCount = primitiveCount,
		.globalSymbolCapacity = primitiveCount
	};

	makeArray(table.globalSymbols, table.globalSymbolCount);

	for (usize i = 0; i < primitiveCount; ++i)
	{
		SymbolData data =
		{
			.symbol = duplicateString(primitives[i].symbol),
			.index = i,
			.type = SYMBOL_PRIMITIVE,
			.isValid = true,
			.isDestroyed = false
		};

		table.globalSymbols[i] = data;
	}

	return table;
}

void symbolTableDestroy(SymbolTable *table)
{
	for (usize i = 0; i < table->globalSymbolCount; ++i)
		symbolDataDestroy(&table->globalSymbols[i]);

	deallocate(table->globalSymbols);

	for (usize i = 0; i < table->localSymbolCount; ++i)
		symbolDataDestroy(&table->localSymbols[i]);

	deallocate(table->localSymbols);

	scopeDestroy(&table->scope);
	deallocate(table->blocks);
}

void symbolTablePushBlock(SymbolTable *table)
{
	assert(table);

	usize index = table->blockCount;

	incrementArray(table->blocks, &table->blockCount, &table->blockCapacity);

	table->blocks[index] = table->localSymbolCount;
}

void symbolTablePopBlock(SymbolTable *table)
{
	assert(table);
	assert(table->blockCount > 0);
	
	usize blockIndex = table->blocks[table->blockCount - 1];

	for (usize i = blockIndex; i < table->localSymbolCount; ++i)
		symbolDataDestroy(table->localSymbols + i);

	table->blockCount -= 1;
	table->localSymbolCount = blockIndex;
}

