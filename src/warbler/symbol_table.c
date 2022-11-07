#include <warbler/symbol_table.h>
#include <warbler/context.h>
#include <warbler/util/array.h>
#include <warbler/syntax.h>
#include <warbler/util/print.h>
#include <warbler/util/memory.h>
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
	
	usize *blocks;
	usize blockCount;
	usize blockCapacity;

	Scope package;

	PackageContext *packages;
	usize packageCount;
	StructContext *structs;
	usize structCount;
	FunctionContext* functions;
	usize functionCount;
	ParameterContext *parameters;
	usize parameterCount;
	VariableContext *variables;
	usize variableCount;

	Validation *validations;
	usize validationCount;

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
			exitWithErrorFmt("Invalid SymbolType for type name: %d", type);
	}
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

static SymbolId *addGlobal(SymbolType type, usize index, const char *symbol, const Token *name)
{
	assert(name);

	SymbolData *previous = findGlobalSymbolData(symbol);

	if (previous)
	{
		printTokenError(name, "'%s' is already declared in this package.", symbol);
		printTokenNote(&previous->name, "Previous declaration here.");

		previous->isValid = false;
		return NULL;
	}

	resizeArray(table.globals, ++table.globalCount);

	SymbolData *data = &table.globals[table.globalCount - 1];
	
	*data = (SymbolData)
	{
		.symbol = duplicateString(symbol),
		.id = {
			.type = type,
			.index = index
		},
		.isValid = true,
		.name = *name
	};

	return &data->id;
}

static SymbolId *addLocal(SymbolType type, usize index, const char *symbol, const Token *name)
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
		.symbol = duplicateString(symbol),
		.id = {
			.type = type,
			.index = index
		},
		.name = *name,
		.isDefined = true,
		.isValid = true
	};

	SymbolId *id = &data->id;

	return id;
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

SymbolId *symbolTableDeclareStruct(const StructSyntax *syntax)
{
	char *symbol = getSymbolFromToken(&syntax->name);
	SymbolId *id = addGlobal(SYMBOL_STRUCT, table.structCount, symbol, &syntax->name);

	if (!id)
		return NULL;
	
	resizeArray(table.structs, ++table.structCount);

	table.structs[id->index] = (StructContext)
	{
		.symbol = symbol
	};

	resizeArray(table.validations, ++table.validationCount);

	table.validations[table.validationCount - 1] = (Validation)
	{
		.structSyntax = syntax,
		.id = *id
	};

	return id;
}

SymbolId *symbolTableDeclareFunction(const FunctionSyntax *syntax)
{
	char *symbol = getSymbolFromToken(&syntax->name);
	SymbolId *id = addGlobal(SYMBOL_FUNCTION, table.functionCount, symbol, &syntax->name);

	if (!id)
		return NULL;

	resizeArray(table.functions, ++table.functionCount);

	table.functions[id->index] = (FunctionContext)
	{
		.symbol = symbol
	};

	resizeArray(table.validations, ++table.validationCount);

	table.validations[table.validationCount - 1] = (Validation)
	{
		.functionSyntax = syntax,
		.id = *id
	};

	return id;
}

SymbolId *symbolTableDeclarePackage(const char *symbol)
{
	resizeArray(table.packages, ++table.packageCount);
	resizeArray(table.globals, ++table.globalCount);

	usize index = table.packageCount - 1;

	table.packages[index] = (PackageContext)
	{
		.symbol = duplicateString(symbol)
	};

	SymbolData *data = &table.globals[table.globalCount - 1];

	*data = (SymbolData)
	{
		.symbol = duplicateString(symbol),
		.id = {
			.type = SYMBOL_PACKAGE,
			.index = index
		},
		.isValid = true
	};

	return &data->id;
}

SymbolId *symbolTableDeclareVariable(const VariableSyntax *syntax)
{
	char *symbol = tokenGetText(&syntax->name);
	SymbolId *id = addLocal(SYMBOL_VARIABLE, table.variableCount, symbol, &syntax->name);

	resizeArray(table.variables, ++table.variableCount);

	table.variables[id->index] = (VariableContext)
	{
		.symbol = symbol
	};

	return id;
}

SymbolId *symbolTableDeclareParameter(const ParameterSyntax *syntax)
{
	char *symbol = tokenGetText(&syntax->name);
	SymbolId *id = addLocal(SYMBOL_PARAMETER, table.parameterCount, symbol, &syntax->name);

	resizeArray(table.variables, ++table.variableCount);

	table.parameters[id->index] = (ParameterContext)
	{
		.symbol = symbol
	};

	return id;
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

char *symbolTableGetSymbolForIdentifier(const const char *identifier)
{
	return scopeCreateSymbol(&table.package, identifier);
}

SymbolId *symbolTableResolve(const char *identifier)
{
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
	String symbol = { 0 };
	Scope *scope = &table.package;

	for (usize i = 0; i < scope->count; ++i)
	{
		stringPushCString(&symbol, scope->names[i]);
		stringPushCString(&symbol, "::");
	}

	stringPushCString(&symbol, identifier);

	return symbol.data;
}

void symbolTableSetScopeFromSymbol(const char *symbol)
{
	table.package.count = 0;

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
	SymbolTable table =
	{
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
				.index = i
			},
			.isValid = true
		};

		table.globals[i] = data;
	}
}

void symbolTableDestroy()
{
	for (usize i = 0; i < table.globalCount; ++i)
		symbolDataDestroy(&table.globals[i]);

	deallocate(table.globals);

	for (usize i = 0; i < table.localCount; ++i)
		symbolDataDestroy(&table.locals[i]);

	deallocate(table.locals);

	scopeDestroy(&table.package);
	deallocate(table.blocks);
}

ProgramContext symbolTableExport()
{
	exitNotImplemented();
	ProgramContext context = { 0 };

	return context;
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

usize symbolTableGetValidationCount()
{
	return table.validationCount;
}

const Validation *symbolTableValidationAt(usize index)
{
	assert(index < table.validationCount);

	return &table.validations[index];
}

VariableContext *symbolTableVariableAt(usize index)
{
	assert(index < table.variableCount);

	return &table.variables[index];
}

ParameterContext *symbolTableParameterAt(usize index)
{
	assert(index < table.parameterCount);

	return &table.parameters[index];
}

FunctionContext *symbolTableFunctionAt(usize index)
{
	assert(index < table.functionCount);
	
	return &table.functions[index];
}

StructContext *symbolTableStructAt(usize index)
{
	assert(index < table.structCount);

	return &table.structs[index];
}

const PrimitiveContext *symbolTablePrimitiveAt(usize index)
{
	assert(index < primitiveCount);

	return &primitives[index];
}
