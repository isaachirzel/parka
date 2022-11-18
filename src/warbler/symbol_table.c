#include <warbler/ast.h>
#include <warbler/conversion.h>
#include <warbler/symbol_table.h>
#include <warbler/util/array.h>
#include <warbler/util/memory.h>
#include <warbler/util/print.h>

#include <assert.h>
#include <string.h>

typedef struct SymbolData
{
	char *symbol;
	SymbolId id;
	bool isValid;
	bool isDefined;
	Token name;
} SymbolData;

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

	Scope package;

	// Contexts
	Package *packages;
	usize packageCount;
	Struct *structs;
	usize structCount;
	Function* functions;
	usize functionCount;
	Parameter *parameters;
	usize parameterCount;
	Variable *variables;
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

static SymbolData *findGlobalSymbolData(const char *symbol)
{
	for (usize i = 0; i < table.globalCount; ++i)
	{
		SymbolData *data = &table.globals[i];

		if (!strcmp(symbol, data->symbol))
			return data;
	}

	return NULL;
}

static SymbolData *findLocalSymbolData(usize blockIndex, const char *symbol)
{
	if (table.localCount == 0)
		return NULL;

	usize i = table.localCount - 1;

	while (true)
	{
		SymbolData *data = &table.locals[i];

		if (!strcmp(symbol, data->symbol))
			return data;

		if (i == blockIndex)
			break;

		i -= 1;
	}

	return NULL;
}

static SymbolData *findBlockSymbolData(const char *symbol)
{
	usize blockIndex = table.blockCount > 0
		? table.blocks[table.blockCount - 1]
		: 0;
	SymbolData *data = findLocalSymbolData(blockIndex, symbol);
	
	return data;
}

static char *getSymbolFromToken(const Token *token)
{
	// TODO: Optimize
	char *name = tokenGetText(token);
	char *symbol = symbolTableCreateSymbol(name);

	deallocate(name);

	return symbol;
}

static bool addGlobal(const SymbolId *id, const char *symbol, const Token *name)
{
	assert(name);

	SymbolData *previous = findGlobalSymbolData(symbol);

	if (previous)
	{
		printTokenError(name, "'%s' is already declared in this package.", symbol);
		printTokenNote(&previous->name, "Previous declaration here.");

		previous->isValid = false;
		return false;
	}

	resizeArray(table.globals, ++table.globalCount);

	SymbolData *data = &table.globals[table.globalCount - 1];
	
	*data = (SymbolData)
	{
		.symbol = stringDuplicate(symbol),
		.id = *id,
		.isValid = true,
		.name = *name
	};

	return true;
}

SymbolId *symbolTableFindGlobal(const char *symbol)
{
	SymbolData *data = findGlobalSymbolData(symbol);
	SymbolId *id = data ? &data->id : NULL;

	return id;
}

SymbolId *symbolTableFindLocal(const char *symbol)
{
	SymbolData *data = findLocalSymbolData(0, symbol);
	SymbolId *id = data ? &data->id : NULL;

	return id;
}

SymbolId *symbolTableFind(const char *symbol)
{
	SymbolId *localId = symbolTableFindLocal(symbol);

	if (localId)
		return localId;

	SymbolId *globalId = symbolTableFindGlobal(symbol);

	return globalId;
}

static bool addLocal(const SymbolId *id, const char *symbol, const Token *name)
{
	SymbolData *previous = findBlockSymbolData(symbol);

	if (previous)
	{
		printTokenError(name, "'%s' is already declared in this block.", symbol);
		printTokenNote(&previous->name, "Previous declaration here.");
		previous->isValid = false;
		return false;
	}

	incrementArray(table.locals, &table.localCount, &table.localCapacity);

	SymbolData *data = &table.locals[table.localCount - 1];

	*data = (SymbolData)
	{
		.symbol = stringDuplicate(symbol),
		.id = *id,
		.name = *name,
		.isDefined = true,
		.isValid = true
	};

	return true;
}

bool symbolTableDeclareGlobal(const SymbolId *id)
{
	printFmt("Declare global: %d, %zu", id->type, id->index);
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
				.isValid = true
			};

			return true;
		}

		case SYMBOL_STRUCT:
		{
			Struct *node = symbolTableGetStruct(id);

			return addGlobal(id, node->symbol, &node->name);
		}

		case SYMBOL_FUNCTION:
		{
			Function *node = symbolTableGetFunction(id);

			return addGlobal(id, node->symbol, &node->name);
		}

		default:
			exitWithErrorFmt("Invalid global symbol type: %d", id->type);
	}
}

bool symbolTableDeclareLocal(const SymbolId *id)
{
	printFmt("Declare local: %d, %zu", id->type, id->index);
	switch (id->type)
	{
		case SYMBOL_VARIABLE:
		{
			Variable *node = symbolTableGetVariable(id);

			return addLocal(id, node->symbol, &node->name);
		}

		case SYMBOL_PARAMETER:
		{
			Parameter *node = symbolTableGetParameter(id);

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

		sbPush(&tmp, *iter);
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
	}
}

SymbolId *symbolTableResolve(const Token *token)
{
	// TODO: Stack
	char *identifier = tokenGetText(token);
	SymbolId *localId = symbolTableFindLocal(identifier);

	if (localId)
		return localId;

	Scope *package = &table.package;

	for (i32 i = (i32)package->count; i >= 0; --i)
	{
		// TODO: Optimize with stack symbol
		char *symbol = scopeCreateSymbolN(package, identifier, i);
		SymbolId *globalId = symbolTableFindGlobal(symbol);

		deallocate(symbol);

		if (globalId)
			return globalId;
	}

	printTokenError(token, "Unable to find '%s' in this scope.", identifier);

	return NULL;
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

char *symbolTableCreateSymbol(const char *identifier)
{
	StringBuilder symbol = { 0 };
	Scope *scope = &table.package;

	for (usize i = 0; i < scope->count; ++i)
	{
		sbPushString(&symbol, scope->names[i]);
		sbPushString(&symbol, "::");
	}

	sbPushString(&symbol, identifier);

	return symbol.data;
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

void symbolTableInitialize()
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
			.isValid = true
		};

		table.globals[i] = data;
	}
}

void symbolTableDestroy()
{
	for (usize i = 0; i < table.globalCount; ++i)
		symbolDataDestroy(&table.globals[i]);

	for (usize i = 0; i < table.localCount; ++i)
		symbolDataDestroy(&table.locals[i]);

	for (usize i = 0; i < table.packageCount; ++i)
		freePackage(&table.packages[i]);

	for (usize i = 0; i < table.structCount; ++i)
		freeStruct(&table.structs[i]);

	for (usize i = 0; i < table.functionCount; ++i)
		freeFunction(&table.functions[i]);

	for (usize i = 0; i < table.parameterCount; ++i)
		freeParameter(&table.parameters[i]);

	for (usize i = 0; i < table.variableCount; ++i)
		freeVariable(&table.variables[i]);

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

void symbolTablePushBlock()
{
	usize index = table.blockCount;

	incrementArray(table.blocks, &table.blockCount, &table.blockCapacity);

	table.blocks[index] = table.localCount;
}

void symbolTablePopBlock()
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

Variable *symbolTableGetVariable(const SymbolId *id)
{
	assert(id->type == SYMBOL_VARIABLE);
	assert(id->index < table.variableCount);

	return &table.variables[id->index];
}

Parameter *symbolTableGetParameter(const SymbolId *id)
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

SymbolId symbolTableAddPackage()
{
	usize index = table.packageCount;

	resizeArray(table.packages, ++table.packageCount);

	table.packages[index] = (Package) { 0 };

	SymbolId id = { SYMBOL_PACKAGE, index };

	return id;
}

SymbolId symbolTableAddStruct()
{
	usize index = table.structCount;

	resizeArray(table.structs, ++table.structCount);

	table.structs[index] = (Struct) { 0 };

	SymbolId id = { SYMBOL_STRUCT, index };

	return id;
}

SymbolId symbolTableAddFunction()
{
	usize index = table.functionCount;

	resizeArray(table.functions, ++table.functionCount);

	table.functions[index] = (Function) { 0 };

	SymbolId id = { SYMBOL_FUNCTION, index };

	return id;
}

SymbolId symbolTableAddVariable()
{
	usize index = table.variableCount;

	resizeArray(table.variables, ++table.variableCount);

	table.variables[index] = (Variable) { 0 };

	SymbolId id = { SYMBOL_VARIABLE, index };

	return id;
}

SymbolId symbolTableAddParameter()
{
	usize index = table.parameterCount;

	resizeArray(table.parameters, ++table.parameterCount);

	table.parameters[index] = (Parameter) { 0 };

	SymbolId id = { SYMBOL_PARAMETER, index };

	return id;
}

usize symbolTablePackageCount()
{
	return table.packageCount;
}
