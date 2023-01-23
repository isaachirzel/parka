#include "warbler/ast.h"
#include "warbler/ast/function.h"
#include "warbler/ast/statement.h"
#include "warbler/symbol_id.h"
#include "warbler/symbol_table.h"
#include "warbler/token.h"
#include "warbler/util/arena.h"
#include "warbler/util/array.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"
#include "warbler/util/string.h"
#include "warbler/util/table.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INITIAL_BLOCK_CAPACITY (3)
#define INITIAL_LOCAL_SYMBOL_CAPACITY (10)

typedef struct GlobalSymbolTable
{
	Table table;
	Arena symbolArena;
	usize symbolCount;

	Arena packageArena;
	usize packageCount;
	Arena structArena;
	usize structCount;
	Arena functionArena;
	usize functionCount;
	Arena variableArena;
	usize variableCount;
	Arena parameterArena;
	usize parameterCount;
} GlobalSymbolTable;

GlobalSymbolTable table;

static inline Symbol *getSymbols()
{
	return table.symbolArena.data;
}

static inline Package *getPackages()
{
	return table.packageArena.data;
}

static inline Struct *getStructs()
{
	return table.structArena.data;
}

static inline Function *getFunctions()
{
	return table.functionArena.data;
}

static inline Variable *getVariables()
{
	return table.variableArena.data;
}

static inline Parameter *getParameters()
{
	return table.parameterArena.data;
}

static inline usize gigabytes(usize count)
{
	return count << 30;
}

static inline usize megabytes(usize count)
{
	return count << 20;
}

static inline usize kilobytes(usize count)
{
	return count << 10;
}

static void symbolDestroy(Symbol *symbol)
{
	assert(symbol->key != NULL);
	
	deallocate(symbol->key);

	symbol->key = NULL;
}

const char *symbolTypeGetName(SymbolType type)
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
			break;
	}

	exitWithErrorFmt("Unable to get name for SymbolType: %d", type);
}

const Token *symbolGetToken(SymbolType type, usize index)
{
	switch (type)
	{
		case SYMBOL_STRUCT:
		{
			Struct *structs = getStructs();
			
			return &structs[index].name;
		}

		case SYMBOL_FUNCTION:
		{
			Function *functions = getFunctions();

			return &functions[index].name;
		}

		case SYMBOL_VARIABLE:
		{
			Variable *variables = getVariables();

			return &variables[index].name;
		}

		case SYMBOL_PARAMETER:
		{
			Parameter *parameters = getParameters();

			return &parameters[index].name;
		}

		default:
			break;
	}

	exitWithErrorFmt("Unable to get Token for Symbol with type: %d", type);
}

static Symbol *findGlobalSymbol(const char *key)
{
	Symbol *symbols = getSymbols();
	usize globalId = tableFind(&table.table, key);

	if (globalId != NOT_FOUND)
		return &symbols[globalId];

	return NULL;
}

static Symbol *findLocalSymbol(LocalSymbolTable *localTable, const char *identifier, usize blockOffset)
{
	if (localTable->symbolCount == 0)
		return NULL;

	usize i = localTable->symbolCount - 1;

	while (i >= blockOffset)
	{
		Symbol *symbol = &localTable->symbols[i];

		if (!strcmp(identifier, symbol->key))
			return symbol;

		i -= 1;
	}

	return NULL;
}

static Symbol *findBlockSymbol(LocalSymbolTable *localTable, const char *identifier)
{
	usize blockOffset = localTable->blockCount > 0
		? localTable->blocks[localTable->blockCount - 1].offset
		: 0;
	Symbol *symbol = findLocalSymbol(localTable, identifier, blockOffset);

	return symbol;
}

const Symbol *symbolTableFind(LocalSymbolTable* localTable, const char *key)
{
	// TODO: Optimize by checking if there are ':' in the name to see if it's a local or global symbol
	Symbol *local = findLocalSymbol(localTable, key, 0);

	if (local)
		return local;

	Symbol *global = findGlobalSymbol(key);

	return global;
}

bool symbolTableDeclareGlobal(SymbolType type, usize index)
{
	const char *key = symbolGetKey(type, index);
	TableEntry *entry = tableGetEntry(&table.table, key);

	printFmt("Declaring %s[%zu]: %s", symbolTypeName(type), index, key);
	
	switch (type)
	{
		case SYMBOL_PACKAGE:
			tableEntryInit(entry, key, index);
			return true;

		case SYMBOL_PRIMITIVE:
			tableEntryInit(entry, key, index);
			return true;

		case SYMBOL_STRUCT:
		case SYMBOL_FUNCTION:
			break;

		default:
			exitWithErrorFmt("Unable to declare global with SymbolType: %d", type);
	}

	usize previousId = tableEntryGetValue(entry);

	if (previousId != NOT_FOUND)
	{
		Symbol *symbols = getSymbols();
		Symbol *previous = &symbols[previousId];

		const Token *name = symbolGetToken(type, index);
		const Token *previousName = symbolGetToken(previous->type, previous->index);

		printTokenError(name, "'%s' is already declared in this package.", key);
		printTokenNote(previousName, "Previous declaration here.");

		previous->status = VALIDATION_INVALID;

		return false;
	}

	tableEntryInit(entry, key, index);

	return true;
}

bool symbolTableDeclareLocal(LocalSymbolTable *localTable, SymbolType type, usize index)
{
	const char *key = symbolGetKey(type, index);

	switch (type)
	{
		case SYMBOL_VARIABLE:
		case SYMBOL_PARAMETER:
			break;
		
		default:
			exitWithErrorFmt("Unable to declare Local with SymbolType: %d", type);
	}

	Symbol *previous = findBlockSymbol(localTable, key);

	if (previous)
	{
		const Token *name = symbolGetToken(type, index);
		const Token *previousName = symbolGetToken(previous->type, previous->index);

		printTokenError(name, "'%s' is already declared in this block.", key);
		printTokenNote(previousName, "Previous declaration here.");

		previous->status = VALIDATION_INVALID;

		return false;
	}

	usize symbolIndex = localTable->symbolCount;

	incrementArray(localTable->symbols, &localTable->symbolCount, &localTable->symbolCapacity);

	localTable->symbols[symbolIndex] = (Symbol)
	{
		.key = stringDuplicate(key),
		.index = index,
		.type = type,
		.status = VALIDATION_PENDING
	};

	return true;
}

static Symbol *symbolTableResolveIdentifier(const Scope *scope, const char *identifier)
{
	Symbol *symbol = NULL;

	for (usize i = scope->count; i > 0; --i)
	{
		char *key = scopeCreateSymbolN(scope, identifier, i);

		symbol = findGlobalSymbol(key);

		deallocate(key);

		if (symbol)
			return symbol;
	}

	symbol = findGlobalSymbol(identifier);

	return symbol;
}

Symbol *symbolTableResolve(LocalSymbolTable *localTable, const Token *token)
{
	// TODO: Optimize symbol handling
	char *identifier = tokenGetText(token);
	Symbol *symbol = findLocalSymbol(localTable, identifier, 0);

	if (!symbol)
		symbol = symbolTableResolveIdentifier(localTable->packageScope, identifier);

	if (!symbol)
		printTokenError(token, "Unable to find '%s' in this scope.", identifier);

	deallocate(identifier);

	return symbol;
}

Symbol *symbolTableResolveGlobal(const Scope *scope, const Token *token)
{
	char *identifier = tokenGetText(token);
	Symbol *symbol = symbolTableResolveIdentifier(scope, identifier);

	if (!symbol)
		printTokenError(token, "Unable to find '%s' in this scope.", identifier);

	deallocate(identifier);

	return symbol;
}

void symbolTableInitialize(const char *projectName)
{
	table = (GlobalSymbolTable)
	{
		.table = tableCreate(128),
		.symbolArena = arenaCreate(megabytes(512)),
		.symbolCount = primitiveCount,
		.packageArena = arenaCreate(megabytes(1)),
		.structArena = arenaCreate(megabytes(128)),
		.functionArena = arenaCreate(megabytes(128)),
		.variableArena = arenaCreate(megabytes(128)),
		.parameterArena = arenaCreate(megabytes(128)),
	};

	Symbol *symbols = arenaAllocate(&table.symbolArena, sizeof(Symbol) * primitiveCount);

	for (usize i = 0; i < primitiveCount; ++i)
	{
		symbols[i] = (Symbol)
		{
			.key = stringDuplicate(primitives[i].symbol),
			.index = i,
			.type = SYMBOL_PRIMITIVE,
			.status = VALIDATION_VALID
		};

		bool successfullyInsertedPrimitive = symbolTableDeclareGlobal(SYMBOL_PRIMITIVE, i);

		assert(successfullyInsertedPrimitive);
	}
}

void symbolTableDestroy(void)
{
	Symbol *symbols = getSymbols();
	Package *packages = getPackages();
	Struct *structs = getStructs();
	Function *functions = getFunctions();
	Variable *variables = getVariables();
	Parameter *parameters = getParameters();

	for (usize i = 0; i < table.symbolCount; ++i)
		symbolDestroy(&symbols[i]);

	for (usize i = 0; i < table.packageCount; ++i)
		packageFree(&packages[i]);

	for (usize i = 0; i < table.structCount; ++i)
		structFree(&structs[i]);

	for (usize i = 0; i < table.functionCount; ++i)
		functionFree(&functions[i]);

	for (usize i = 0; i < table.variableCount; ++i)
		variableFree(&variables[i]);

	for (usize i = 0; i < table.parameterCount; ++i)
		parameterFree(&parameters[i]);

	tableDestroy(&table.table);
	arenaDestroy(&table.symbolArena);
	arenaDestroy(&table.packageArena);
	arenaDestroy(&table.structArena);
	arenaDestroy(&table.functionArena);
	arenaDestroy(&table.variableArena);
	arenaDestroy(&table.parameterArena);
}

Symbol *symbolTableGetSymbol(usize index)
{
	assert(index < table.symbolCount);

	Symbol *symbols = getSymbols();

	return &symbols[index];
}

Package *symbolTableGetPackage(usize index)
{
	assert(index < table.packageCount);

	Package *packages = getPackages();

	return &packages[index];
}

Variable *symbolTableGetVariable(usize index)
{
	assert(index < table.variableCount);

	Variable *variables = getVariables();

	return &variables[index];
}

Parameter *symbolTableGetParameter(usize index)
{
	assert(index < table.parameterCount);
	
	Parameter *parameters = getParameters();

	return &parameters[index];
}

Function *symbolTableGetFunction(usize index)
{
	assert(index < table.functionCount);
	
	Function *functions = getFunctions();

	return &functions[index];
}

Struct *symbolTableGetStruct(usize index)
{
	assert(index < table.structCount);

	Struct *structs = getStructs();

	return &structs[index];
}

const Primitive *symbolTableGetPrimitive(usize index)
{
	assert(index < primitiveCount);

	return &primitives[index];
}

usize symbolTableAddPackage(void)
{
	usize index = table.packageCount;
	Package *package = arenaAllocate(&table.packageArena, sizeof(Package));

	*package = (Package) { 0 };
	++table.packageCount;

	return index;
}

usize symbolTableAddStruct(void)
{
	usize index = table.structCount;
	Struct *node = arenaAllocate(&table.structArena, sizeof(Struct));
	
	*node = (Struct) { 0 };
	++table.structCount;

	return index;
}

usize symbolTableAddFunction(void)
{
	usize index = table.functionCount;
	Function *node = arenaAllocate(&table.functionArena, sizeof(Function));

	*node = (Function) { 0 };
	++table.functionCount;

	return index;
}

usize symbolTableAddVariable(void)
{
	usize index = table.variableCount;
	Variable *node = arenaAllocate(&table.variableArena, sizeof(Variable));

	*node = (Variable) { 0 };
	++table.variableCount;

	return index;
}

usize symbolTableAddParameter(void)
{
	usize index = table.parameterCount;
	Parameter *node = arenaAllocate(&table.parameterArena, sizeof(Parameter));

	*node = (Parameter) { 0 };
	++table.parameterCount;

	return index;
}

static usize getEntityCount(SymbolType type)
{
	switch (type)
	{
		case SYMBOL_PACKAGE:
			return table.packageCount;

		case SYMBOL_STRUCT:
			return table.structCount;

		case SYMBOL_PRIMITIVE:
			return primitiveCount;

		case SYMBOL_FUNCTION:
			return table.functionCount;

		case SYMBOL_VARIABLE:
			return table.variableCount;

		case SYMBOL_PARAMETER:
			return table.parameterCount;

		default:
			break;
	}

	exitWithErrorFmt("Unable to get entity count for symbol type: %d", type);
}

bool symbolTableForEachEntity(SymbolType type, IdAction action)
{
	bool success = true;

	usize count = getEntityCount(type);

	for (usize i = 0; i < count; ++i)
	{
		if (!action(i))
			success = false;
	}

	return success;
}

bool symbolTableForEachGlobal(SymbolAction action)
{
	bool success = true;
	Symbol *symbols = getSymbols();

	for (usize i = 0; i < table.symbolCount; ++i)
	{
		if (!action(&symbols[i]))
			success = false;
	}

	return success;
}

usize symbolTablePackageCount(void)
{
	return table.packageCount;
}

const char *symbolGetKey(SymbolType type, usize index)
{
	switch (type)
	{
		case SYMBOL_PACKAGE:
		{
			const Package *node = symbolTableGetPackage(index);

			return node->symbol;
		}

		case SYMBOL_STRUCT:
		{
			const Struct *node = symbolTableGetStruct(index);

			return node->symbol;
		}

		case SYMBOL_PRIMITIVE:
		{
			const Primitive *node = symbolTableGetPrimitive(index);

			return node->symbol;
		}

		case SYMBOL_FUNCTION:
		{
			Function *node = symbolTableGetFunction(index);

			return node->symbol;
		}

		case SYMBOL_VARIABLE:
		{
			Variable *node = symbolTableGetVariable(index);

			return node->symbol;
		}

		case SYMBOL_PARAMETER:
		{
			Parameter *node = symbolTableGetParameter(index);

			return node->symbol;
		}
	}
}

LocalSymbolTable localSymbolTableCreate(const Scope *packageScope)
{
	LocalSymbolTable table =
	{
		.symbols = allocateArray(sizeof(Symbol), INITIAL_LOCAL_SYMBOL_CAPACITY),
		.symbolCapacity = INITIAL_LOCAL_SYMBOL_CAPACITY,
		.blocks = allocateArray(sizeof(BlockInfo), INITIAL_BLOCK_CAPACITY),
		.blockCapacity = INITIAL_BLOCK_CAPACITY,
		.packageScope = packageScope
	};
	
	return table;
}

void localSymbolTableDestroy(LocalSymbolTable *localTable)
{
	for (usize i = 0; i < localTable->symbolCount; ++i)
		symbolDestroy(&localTable->symbols[i]);
	
	deallocate(localTable->symbols);
	deallocate(localTable->blocks);
}

void localSymbolTableClear(LocalSymbolTable *localTable)
{
	for (usize i = 0; i < localTable->symbolCount; ++i)
		symbolDestroy(&localTable->symbols[i]);

	localTable->function = NULL;
	localTable->symbolCount = 0;
	localTable->blockCount = 0;
}

void localSymbolTablePushBlock(LocalSymbolTable *localTable, Block *block)
{
	usize index = localTable->blockCount;

	incrementArray(localTable->blocks, &localTable->blockCount, &localTable->blockCapacity);

	localTable->blocks[index] = (BlockInfo)
	{
		.node = block,
		.offset = localTable->symbolCount
	};
}

void localSymbolTablePopBlock(LocalSymbolTable *localTable)
{
	assert(localTable->blockCount > 0);
	
	BlockInfo *block = &localTable->blocks[localTable->blockCount - 1];

	for (usize i = block->offset; i < localTable->symbolCount; ++i)
		symbolDestroy(&localTable->symbols[i]);

	localTable->blockCount -= 1;
	localTable->symbolCount = block->offset;
}

Block *localSymbolTableGetCurrentBlock(LocalSymbolTable * restrict localTable)
{
	if (localTable->blockCount == 0)
		return NULL;

	BlockInfo *info = &localTable->blocks[localTable->blockCount - 1];

	return info->node;
}
