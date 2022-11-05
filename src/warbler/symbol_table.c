#include <warbler/symbol_table.h>
#include <warbler/context.h>
#include <warbler/util/array.h>
#include <warbler/syntax.h>
#include <warbler/util/print.h>
#include <warbler/util/memory.h>
#include <assert.h>
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
			exitWithErrorFmt("Invalid SymbolType for type name: %d", type);
	}
}

SymbolData *symbolTableFindGlobal(SymbolTable *table, const char *symbol)
{
	for (usize i = 0; i < table->globalCount; ++i)
	{
		SymbolData *data = table->globals + i;

		if (!strcmp(symbol, data->symbol))
			return data;
	}

	return NULL;
}

static SymbolData *symbolTableFindLocalFromIndex(SymbolTable *table, usize index, const char *symbol)
{
	if (table->localCount == 0)
		return NULL;

	usize i = table->localCount - 1;

	while (true)
	{
		SymbolData *data = table->locals + i;

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

SymbolData *symbolTableDeclareLocal(SymbolTable *table, const char *symbol)
{
	SymbolData *previous = symbolTableFindBlockLocal(table, symbol);

	if (previous)
	{
		printError("'%s' is already declared in this block.", symbol);
		// printNote("Previous declaration here.");
		return NULL;
	}

	usize index = table->localCount;

	incrementArray(table->locals, &table->localCount, &table->localCapacity);

	SymbolData *ptr = table->locals + index;
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

char *symbolTableGetSymbolForIdentifier(const SymbolTable *table, const char *identifier)
{
	return scopeCreateSymbol(&table->package, identifier);
}

SymbolData *symbolTableResolve(SymbolTable *table, const char *identifier)
{
	ProgramContext *program = table->program;
	
	SymbolData *local = symbolTableFindFunctionLocal(table, identifier);

	if (local)
		return local;

	for (i32 i = (i32)program->packageCount; i >= 0; --i)
	{
		// TODO: Optimize with stack symbol
		char *symbol = scopeCreateSymbolN(&table->package, identifier, i);
		SymbolData *iter = symbolTableFindGlobal(table, symbol);

		deallocate(symbol);

		if (iter)
			return iter;
	}

	return NULL;
}

SymbolData *symbolTableDeclareGlobal(SymbolTable *table, const char *symbol)
{
	SymbolData *previous = symbolTableFindGlobal(table, symbol);

	if (previous)
	{
		previous->isValid = false;
		return NULL;
	}

	usize index = table->globalCount;

	resizeArray(table->globals, ++table->globalCount);

	SymbolData *ptr = &table->globals[table->globalCount - 1];

	*ptr = (SymbolData)
	{
		.symbol = duplicateString(symbol),
		.isValid = true
	};

	return ptr;
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

char *symbolTableCreateSymbol(SymbolTable *table, const char *identifier)
{
	String symbol = { 0 };
	Scope *scope = &table->package;

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
	table->package.count = 0;

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

			scopePush(&table->package, buffer);

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
		.program = context,
		.globalCount = primitiveCount,
		.globalCapacity = primitiveCount
	};

	makeArray(table.globals, table.globalCount);

	for (usize i = 0; i < primitiveCount; ++i)
	{
		SymbolData data =
		{
			.symbol = duplicateString(primitives[i].symbol),
			.id = {
				.type = SYMBOL_PRIMITIVE,
				.global = i
			},
			.isValid = true
		};

		table.globals[i] = data;
	}

	return table;
}

void symbolTableDestroy(SymbolTable *table)
{
	for (usize i = 0; i < table->globalCount; ++i)
		symbolDataDestroy(&table->globals[i]);

	deallocate(table->globals);

	for (usize i = 0; i < table->localCount; ++i)
		symbolDataDestroy(&table->locals[i]);

	deallocate(table->locals);

	scopeDestroy(&table->package);
	deallocate(table->blocks);
}

void symbolTablePushBlock(SymbolTable *table)
{
	assert(table);

	usize index = table->blockCount;

	incrementArray(table->blocks, &table->blockCount, &table->blockCapacity);

	table->blocks[index] = table->localCount;
}

void symbolTablePopBlock(SymbolTable *table)
{
	assert(table);
	assert(table->blockCount > 0);
	
	usize blockIndex = table->blocks[table->blockCount - 1];

	for (usize i = blockIndex; i < table->localCount; ++i)
		symbolDataDestroy(table->locals + i);

	table->blockCount -= 1;
	table->localCount = blockIndex;
}

