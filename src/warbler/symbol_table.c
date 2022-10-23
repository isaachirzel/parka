#include <warbler/symbol_table.h>
#include <warbler/context.h>
#include <warbler/util/array.h>
#include <warbler/syntax.h>
#include <warbler/util/print.h>

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

SymbolData *symbolTableFindLocal(SymbolTable *table, const char *symbol)
{
	for (i32 i = (i32)table->localSymbolCount; i >= 0; --i)
	{
		SymbolData *data = table->localSymbols + i;

		if (!strcmp(symbol, data->symbol))
			return data;
	}

	return NULL;
}

SymbolData *symbolTableFind(SymbolTable *table, const char *symbol)
{
	SymbolData *functionSymbol = symbolTableFindLocal(table, symbol);

	if (functionSymbol)
		return functionSymbol;

	SymbolData *globalSymbol = symbolTableFindGlobal(table, symbol);

	return globalSymbol;
}

/**
 * @return On success, NULL. On failure, a pointer to the symbol with the same name
 */
AddSymbolResult symbolTableAddLocal(SymbolTable *table, SymbolData *data)
{
	SymbolData *previous = symbolTableFindLocal(table, data->symbol);

	// TODO: Highlight errors
	// TODO: Soft allow adding the symbol

	if (previous)
	{
		Token *token;

		const char *typeName = getSymbolTypeName(previous->type);

		printTokenError(&previous->parameterSyntax->name, "A %s with the '%s' is already declared in this function.", typeName, data->symbol);

		return (AddSymbolResult) { false, previous };
	}

	if (table->localSymbolCapacity == table->localSymbolCount)
	{
		// TODO: resize in bigger chunks
		resizeArray(table->localSymbols, ++table->localSymbolCapacity);
	}

	usize index = table->localSymbolCount;

	table->localSymbols[index] = *data;
	++table->localSymbolCount;

	return (AddSymbolResult) { false, table->localSymbols + index };
}

/**
 * @return NULL on success, a pointer to the symbol with the same name on failure
 */
AddSymbolResult symbolTableAddGlobal(SymbolTable *table, SymbolData *data)
{
	SymbolData *previousDeclaration = symbolTableFindGlobal(table, data->symbol);

	if (previousDeclaration)
	{
		const Token *token;

		switch (data->type)
		{
			case SYMBOL_PACKAGE:
			case SYMBOL_PRIMITIVE:
				exitWithError("Duplicate symbol in table: %s", data->symbol);

			case SYMBOL_STRUCT:
				token = &data->structSyntax->name;
				break;

			case SYMBOL_FUNCTION:
				token = &data->functionSyntax->name;
				break;

			default:
				exitWithError("Invalid SymbolType: %d", data->type);

		}

		printTokenError(&data->functionSyntax->name, "%s '%s' is already defined as a %s.", getSymbolTypeName(data->type), data->symbol, getSymbolTypeName(previousDeclaration->type));

		switch (previousDeclaration->type)
		{
			case SYMBOL_STRUCT:
				printTokenNote(&previousDeclaration->structSyntax->name, "Previous declaration here.");
				break;

			case SYMBOL_FUNCTION:
				printTokenNote(&previousDeclaration->functionSyntax->name, "Previous declaration here.");
				break;

			default:
				break;
		}

		return (AddSymbolResult) { false, previousDeclaration };
	}

	usize index = table->globalSymbolCount;

	resizeArray(table->globalSymbols, ++table->globalSymbolCount);

	table->globalSymbols[index] = *data;

	return (AddSymbolResult) { true, table->globalSymbols + index };
}

static SymbolData createPrimitiveSymbol(const PrimitiveContext *primitive, usize index)
{
	SymbolData data =
	{
		.symbol = duplicateString(primitive->symbol),
		.index = index,
		.type = SYMBOL_PRIMITIVE,
		.status = VALIDATION_VALID
	};

	return data;
}

static SymbolData createStructSymbol(const StructSyntax *syntax, const char *scope)
{
	// TODO: Safety check
	static char name[256];
	String symbol = stringFrom(scope);

	copyToken(name, &syntax->name);
	stringPush(&symbol, name);

	SymbolData data =
	{
		.symbol = symbol.data,
		.type = SYMBOL_STRUCT,
		.status = VALIDATION_NOT_YET
	};

	return data;
}

static SymbolData createFunctionSymbol(const FunctionSyntax *syntax, const char *scope)
{
	// TODO: Safety check
	static char name[256];
	String symbol = stringFrom(scope);
	
	copyToken(name, &syntax->name);
	stringPush(&symbol, name);

	SymbolData data =
	{
		.symbol = symbol.data,
		.type = SYMBOL_FUNCTION,
		.status = VALIDATION_NOT_YET
	};

	return data;
}

bool addGlobalSymbols(SymbolTable *table, const ProgramSyntax *syntax)
{
	SymbolData *symbols = table->globalSymbols;

	resizeArray(table->globalSymbols, primitiveCount);

	table->globalSymbolCount = primitiveCount;

	for (usize i = 0; i < primitiveCount; ++i)
	{
		const PrimitiveContext *context = primitives + i;

		table->globalSymbols[i] = createPrimitiveSymbol(primitives + i, i);
	}

	bool success = true;

	for (usize i = 0; i < syntax->packageCount; ++i)
	{
		const PackageSyntax *package = syntax->packages + i;

		static char scope[256];
		static char name[256];

		// TODO: Optimize string copy and safety check
		strcpy(scope, package->name);
		strcat(scope, "::");

		for (usize j = 0; j < package->structCount; ++j)
		{
			SymbolData data = createStructSymbol(package->structs + j, scope);
			AddSymbolResult result = symbolTableAddGlobal(table, &data);

			success = success && result.success;
		}

		for (usize j = 0; j < package->functionCount; ++j)
		{
			SymbolData data = createFunctionSymbol(package->functions + j, scope);
			AddSymbolResult result = symbolTableAddGlobal(table, &data);

			success = success && result.success;
		}
	}

	return success;
}

static char *createSymbol(char **packages, usize count, const char *identifier)
{
	String symbol;

	stringReserve(&symbol, 128);

	for (usize i = 0; i < count; ++i)
	{
		const char *package = packages[i];

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
	return createSymbol(table->packages, table->packageCount, identifier);
}

SymbolData *symbolTableResolve(SymbolTable *table, const char *identifier)
{
	for (i32 i = (i32)table->packageCount; i >= 0; --i)
	{
		char *symbol = createSymbol(table->packages, i, identifier);
		SymbolData *iter = symbolTableFind(table, symbol);

		deallocate(symbol);

		if (iter)
			return iter;
	}

	return NULL;
}

AddSymbolResult symbolTableAddParameter(SymbolTable *table, const ParameterSyntax *syntax)
{
	String symbol = stringFromToken(&syntax->name);
	SymbolData data =
	{
		.parameterSyntax = syntax,
		.symbol = symbol.data,
		.type = SYMBOL_PARAMETER,
		.status = VALIDATION_NOT_YET,
		.isDestroyed = false
	};

	return symbolTableAddLocal(table, &data);
}

AddSymbolResult symbolTableAddVariable(SymbolTable *table, const VariableSyntax *syntax)
{
	String symbol = stringFromToken(&syntax->name);
	SymbolData data =
	{
		.variableSyntax = syntax,
		.symbol = symbol.data,
		.type = SYMBOL_VARIABLE,
		.status = VALIDATION_NOT_YET,
		.isDestroyed = false
	};

	return symbolTableAddLocal(table, &data);
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

void symbolDataValidate(SymbolData *symbol, usize index)
{
	symbol->index = index;
	symbol->status = VALIDATION_VALID;
}

void symbolDataInvalidate(SymbolData *symbol)
{
	symbol->status = VALIDATION_INVALID;
}

void symbolDataDestroy(SymbolData *symbol)
{
	symbol->isDestroyed = true;
}

void symbolDataReinitialize(SymbolData *symbol)
{
	symbol->isDestroyed = false;
}

void symbolTableValidateVariable(SymbolTable *table, SymbolData *data, VariableContext *context)
{
	usize index = table->variableCount;

	resizeArray(table->variables, ++table->variableCount);
	table->variables[index] = *context;

	symbolDataValidate(data, index);
}

void symbolTableValidateParameter(SymbolTable *table, SymbolData *data, ParameterContext *context)
{
	usize index = table->parameterCount;

	resizeArray(table->parameters, ++table->parameterCount);
	table->parameters[index] = *context;

	symbolDataValidate(data, index);
}

void symbolTableValidateStruct(SymbolTable *table, SymbolData *data, StructContext *context)
{
	usize index = table->structCount;

	resizeArray(table->structs, ++table->structCount);
	table->structs[index] = *context;

	symbolDataValidate(data, index);
}

void symbolTableValidateFunction(SymbolTable *table, SymbolData *data, FunctionContext *context)
{
	usize index = table->functionCount;

	resizeArray(table->functions, ++table->functionCount);
	table->functions[index] = *context;

	symbolDataValidate(data, index);
}
