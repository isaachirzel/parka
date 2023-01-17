#include <warbler/symbol_id.h>
#include <warbler/type.h>
#include <warbler/ast.h>
#include <warbler/symbol_table.h>
#include <warbler/util/array.h>
#include <warbler/util/memory.h>
#include <warbler/util/print.h>

#include <assert.h>
#include <string.h>

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

	// Local block indeces	
	usize *blocks;
	usize blockCount;
	usize blockCapacity;

	// State >:(
	Scope package;
	Function *currentFunction;
	Block *currentBlock;

	// Contexts
	Package *packages;
	usize packageCount;
	Struct *structs;
	usize structCount;
	Function* functions;
	usize functionCount;
	Local *parameters;
	usize parameterCount;
	Local *variables;
	usize variableCount;
	Literal *constants;
	usize constantCount;

} SymbolTable;

SymbolTable table;

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

	exitWithErrorFmt("Invalid SymbolType for type name: %d", type);
}

static SymbolData *findGlobalSymbol(const char *symbol)
{
	for (usize i = 0; i < table.globalCount; ++i)
	{
		SymbolData *data = &table.globals[i];

		if (!strcmp(symbol, data->symbol))
			return data;
	}

	return NULL;
}

static SymbolData *findLocalSymbol(const char *identifier, usize blockIndex)
{
	if (table.localCount == 0)
		return NULL;

	usize i = table.localCount - 1;

	while (true)
	{
		SymbolData *data = &table.locals[i];

		if (!strcmp(identifier, data->symbol))
			return data;

		if (i == blockIndex)
			break;

		i -= 1;
	}

	return NULL;
}

static SymbolData *findBlockSymbol(const char *identifier)
{
	usize blockIndex = table.blockCount > 0
		? table.blocks[table.blockCount - 1]
		: 0;

	return findLocalSymbol(identifier, blockIndex);
}

static bool declareGlobal(const SymbolId *id, const char *symbol, const Token *name)
{
	assert(name);
	assert(id->type != SYMBOL_PACKAGE);

	SymbolData *previous = findGlobalSymbol(symbol);

	if (previous)
	{
		const Token *previousName = symbolTableGetToken(&previous->id);

		printTokenError(name, "'%s' is already declared in this package.", symbol);
		printTokenNote(previousName, "Previous declaration here.");

		previous->status = VALIDATION_INVALID;
		return false;
	}

	resizeArray(table.globals, ++table.globalCount);

	SymbolData *data = &table.globals[table.globalCount - 1];
	
	*data = (SymbolData)
	{
		.symbol = stringDuplicate(symbol),
		.id = *id,
		.status = VALIDATION_PENDING
	};

	return true;
}

const SymbolData *symbolTableFind(const char *symbol)
{
	const SymbolData *local = findLocalSymbol(symbol, 0);

	if (local)
		return local;

	const SymbolData *global = findGlobalSymbol(symbol);

	return global;
}

static bool addLocal(const SymbolId *id, const char *symbol, const Token *name)
{
	SymbolData *previous = findBlockSymbol(symbol);

	if (previous)
	{
		const Token *previousName = symbolTableGetToken(&previous->id);

		printTokenError(name, "'%s' is already declared in this block.", symbol);
		printTokenNote(previousName, "Previous declaration here.");
		previous->status = VALIDATION_INVALID;
		return false;
	}

	incrementArray(table.locals, &table.localCount, &table.localCapacity);

	SymbolData *data = &table.locals[table.localCount - 1];

	*data = (SymbolData)
	{
		.symbol = stringDuplicate(symbol),
		.id = *id,
		.status = VALIDATION_INVALID
	};

	return true;
}

bool symbolTableDeclareGlobal(const SymbolId *id)
{
	printFmt("Declaring %s[%zu]: %s", symbolTypeName(id->type), id->index, symbolTableGetSymbol(id));
	
	switch (id->type)
	{
		case SYMBOL_PACKAGE:
		{
			Package *package = symbolTableGetPackage(id);

			resizeArray(table.globals, ++table.globalCount);	

			SymbolData *data = &table.globals[table.globalCount - 1];

			*data = (SymbolData)
			{
				.symbol = stringDuplicate(package->symbol),
				.id = *id,
				.status = VALIDATION_PENDING
			};

			return true;
		}

		case SYMBOL_STRUCT:
		{
			Struct *node = symbolTableGetStruct(id);

			return declareGlobal(id, node->symbol, &node->name);
		}

		case SYMBOL_FUNCTION:
		{
			Function *node = symbolTableGetFunction(id);

			return declareGlobal(id, node->symbol, &node->name);
		}

		default:
			exitWithErrorFmt("Invalid global symbol type: %d", id->type);
	}
}

bool symbolTableDeclareLocal(const SymbolId *id)
{
	printFmt("Declaring %s[%zu]: %s", symbolTypeName(id->type), id->index, symbolTableGetSymbol(id));
	
	switch (id->type)
	{
		case SYMBOL_VARIABLE:
		{
			Local *node = symbolTableGetVariable(id);

			return addLocal(id, node->symbol, &node->name);
		}

		case SYMBOL_PARAMETER:
		{
			Local *node = symbolTableGetParameter(id);

			return addLocal(id, node->symbol, &node->name);
		}
		
		default:
			break;
	}

	exitWithErrorFmt("Invalid local symbol type: %d", id->type);
}

void symbolTableSetScope(const char *symbol)
{
	assert(symbol != NULL);

	// TODO: Clear current package

	StringBuilder tmp;

	sbReserve(&tmp, 64);

	// split symbol by '::'
	for (const char *iter = symbol; *iter; ++iter)
	{
		if (*iter == ':')
		{
			assert(iter[1] == ':');
			// TODO: push currentPackage tmp
			sbClear(&tmp);
			++iter;
			continue;
		}

		sbPushChar(&tmp, *iter);
	}
}

const char *symbolTableGetSymbol(const SymbolId *id)
{
	switch (id->type)
	{
		case SYMBOL_PACKAGE:
			return table.packages[id->index].symbol;
		case SYMBOL_STRUCT:
			return table.structs[id->index].symbol;
		case SYMBOL_PRIMITIVE:
			return primitives[id->index].symbol;
		case SYMBOL_FUNCTION:
			return table.functions[id->index].symbol;
		case SYMBOL_VARIABLE:
			return table.variables[id->index].symbol;
		case SYMBOL_PARAMETER:
			return table.parameters[id->index].symbol;
		default:
			break;
	}

	exitWithErrorFmt("Unable to get symbol for invalid symbol type: %d", id->type);
}

const Token *symbolTableGetToken(const SymbolId *id)
{
	switch (id->type)
	{
		case SYMBOL_STRUCT:
		{
			Struct *node = symbolTableGetStruct(id);
			return &node->name;
		}
		case SYMBOL_FUNCTION:
		{
			Function *node = symbolTableGetFunction(id);
			return &node->name;
		}
		case SYMBOL_VARIABLE:
		{
			Local *node = symbolTableGetVariable(id);
			return &node->name;
		}
		case SYMBOL_PARAMETER:
		{
			Local *node = symbolTableGetParameter(id);
			return &node->name;
		}
		default:
			exitWithErrorFmt("Unable to get token for symbol type: %d", id->type);
	}
}

static SymbolData *symbolTableResolveIdentifier(const char *identifier)
{
	// TODO: Optimize symbol handling
	SymbolData *local = findLocalSymbol(identifier, 0);

	if (local)
		return local;

	Scope *package = &table.package;

	for (usize i = package->count; i > 0; --i)
	{
		char *symbol = scopeCreateSymbolN(package, identifier, i);
		SymbolData *global = findGlobalSymbol(symbol);

		deallocate(symbol);

		if (global)
			return global;
	}

	SymbolData *primitive = findGlobalSymbol(identifier);

	return primitive;
}

SymbolData *symbolTableResolve(const Token *token)
{
	// TODO: Optimize symbol handling
	char *identifier = tokenGetText(token);
	SymbolData *data = symbolTableResolveIdentifier(identifier);

	if (!data)
		printTokenError(token, "Unable to find '%s' in this scope.", identifier);

	deallocate(identifier);

	return data;
}

char *symbolTableCreateSymbol(const char *identifier)
{
	return scopeCreateSymbol(&table.package, identifier);
}

char *symbolTableCreateTokenSymbol(const Token *token)
{
	char *identifier = tokenGetText(token);
	char *symbol = symbolTableCreateSymbol(identifier);

	deallocate(identifier);

	return symbol;
}

void symbolTableSetScopeFromSymbol(const char *symbol)
{
	table.package.count = 0;

	static char buffer[256];
	usize size = 0;

	for (const char *iter = symbol; *iter; ++iter)
	{
		if (*iter == ':')
		{
			iter += 1;
			assert(*iter == ':');

			buffer[size] = 0;
			size = 0;

			scopePush(&table.package, buffer);

			continue;
		}

		buffer[size++] = *iter;
	}
}

void symbolDataDestroy(SymbolData *data)
{
	deallocate(data->symbol);
}

void symbolTableInitialize(const char *projectName)
{
	table = (SymbolTable)
	{
		.globalCount = primitiveCount,
		.globalCapacity = primitiveCount
	};

	makeArray(table.globals, table.globalCount);

	for (usize i = 0; i < primitiveCount; ++i)
	{
		SymbolData data =
		{
			.symbol = stringDuplicate(primitives[i].symbol),
			.id = { SYMBOL_PRIMITIVE, i },
			.status = VALIDATION_VALID
		};

		table.globals[i] = data;
	}

	scopePush(&table.package, projectName);
}

void symbolTableDestroy(void)
{
	for (usize i = 0; i < table.globalCount; ++i)
		symbolDataDestroy(&table.globals[i]);

	for (usize i = 0; i < table.localCount; ++i)
		symbolDataDestroy(&table.locals[i]);

	for (usize i = 0; i < table.packageCount; ++i)
		packageFree(&table.packages[i]);

	for (usize i = 0; i < table.structCount; ++i)
		structFree(&table.structs[i]);

	for (usize i = 0; i < table.functionCount; ++i)
		functionFree(&table.functions[i]);

	for (usize i = 0; i < table.parameterCount; ++i)
		parameterFree(&table.parameters[i]);

	for (usize i = 0; i < table.variableCount; ++i)
		variableFree(&table.variables[i]);

	scopeDestroy(&table.package);

	deallocate(table.globals);
	deallocate(table.locals);
	deallocate(table.blocks);
	deallocate(table.packages);
	deallocate(table.structs);
	deallocate(table.functions);
	deallocate(table.parameters);
	deallocate(table.variables);

	table = (SymbolTable) { 0 };
}

void symbolTablePushBlock(void)
{
	usize index = table.blockCount;

	incrementArray(table.blocks, &table.blockCount, &table.blockCapacity);

	table.blocks[index] = table.localCount;
}

void symbolTablePopBlock(void)
{
	assert(table.blockCount > 0);
	
	usize blockIndex = table.blocks[table.blockCount - 1];

	for (usize i = blockIndex; i < table.localCount; ++i)
		symbolDataDestroy(table.locals + i);

	table.blockCount -= 1;
	table.localCount = blockIndex;
}

Package *symbolTableGetPackage(const SymbolId *id)
{
	assert(id->type == SYMBOL_PACKAGE);
	assert(id->index < table.packageCount);

	return &table.packages[id->index];
}

Local *symbolTableGetVariable(const SymbolId *id)
{
	assert(id->type == SYMBOL_VARIABLE);
	assert(id->index < table.variableCount);

	return &table.variables[id->index];
}

Local *symbolTableGetParameter(const SymbolId *id)
{
	assert(id->type == SYMBOL_PARAMETER);
	assert(id->index < table.parameterCount);

	return &table.parameters[id->index];
}

Function *symbolTableGetFunction(const SymbolId *id)
{
	assert(id->type == SYMBOL_FUNCTION);
	assert(id->index < table.functionCount);
	
	return &table.functions[id->index];
}

Struct *symbolTableGetStruct(const SymbolId *id)
{
	assert(id->type == SYMBOL_STRUCT);
	assert(id->index < table.structCount);

	return &table.structs[id->index];
}

const Primitive *symbolTableGetPrimitive(const SymbolId *id)
{
	assert(id->type == SYMBOL_PRIMITIVE);
	assert(id->index < primitiveCount);

	return &primitives[id->index];
}

Function *symbolTableSelectFunction(const SymbolId *id)
{
	assert(table.currentFunction == NULL);

	Function *function = symbolTableGetFunction(id);

	table.currentFunction = function;

	return function;
}

Function *symbolTableGetSelectedFunction(void)
{
	assert(table.currentFunction != NULL);

	return table.currentFunction;
}

void symbolTableDeselectFunction(void)
{
	assert(table.currentFunction != NULL);

	table.currentFunction = NULL;
}

void symbolTableSelectBlock(Block *block)
{
	assert(table.currentBlock == NULL);

	table.currentBlock = block;
}

Block *symbolTableGetSelectedBlock(void)
{
	assert(table.currentBlock != NULL);

	return table.currentBlock;
}

void symbolTableDeselectBlock(void)
{
	assert(table.currentBlock != NULL);

	table.currentBlock = NULL;
}

SymbolId symbolTableAddPackage(void)
{
	usize index = table.packageCount;

	resizeArray(table.packages, ++table.packageCount);

	table.packages[index] = (Package) { 0 };

	SymbolId id = { SYMBOL_PACKAGE, index };

	return id;
}

SymbolId symbolTableAddStruct(void)
{
	usize index = table.structCount;

	resizeArray(table.structs, ++table.structCount);

	table.structs[index] = (Struct) { 0 };

	SymbolId id = { SYMBOL_STRUCT, index };

	return id;
}

SymbolId symbolTableAddFunction(void)
{
	usize index = table.functionCount;

	resizeArray(table.functions, ++table.functionCount);

	table.functions[index] = (Function) {
		.parameterIds = {
			.type = SYMBOL_PARAMETER
		}
	};

	SymbolId id = { SYMBOL_FUNCTION, index };

	return id;
}

SymbolId symbolTableAddVariable(void)
{
	usize index = table.variableCount;

	resizeArray(table.variables, ++table.variableCount);

	table.variables[index] = (Local) { 0 };

	SymbolId id = { SYMBOL_VARIABLE, index };

	return id;
}

SymbolId symbolTableAddParameter(void)
{
	usize index = table.parameterCount;

	resizeArray(table.parameters, ++table.parameterCount);

	table.parameters[index] = (Local) { 0 };

	SymbolId id = { SYMBOL_PARAMETER, index };

	return id;
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

bool symbolTableForEachEntity(SymbolType type, SymbolIdAction action)
{
	bool success = true;

	usize count = getEntityCount(type);

	for (usize i = 0; i < count; ++i)
	{
		SymbolId id = { type, i };

		if (!action(&id))
			success = false;
	}

	return success;
}

bool symbolTableForEachGlobal(SymbolDataAction action)
{
	bool success = true;

	for (usize i = 0; i < table.globalCount; ++i)
	{
		if (!action(&table.globals[i]))
			success = false;
	}

	return success;
}

usize symbolTablePackageCount(void)
{
	return table.packageCount;
}
