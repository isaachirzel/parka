#include "parka/ast/module.h"
#include "parka/ast/function.h"
#include "parka/ast/struct.h"
#include "parka/token.h"
#include "parka/util/array.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseModule(Module *node, const File *file, const char *package)
{
	// TODO: parse error recovery
	bool success = true;
	Token token = getInitialToken(file);

	arrayInit(&node->functionIds, 5);
	arrayInit(&node->structIds, 2);

parse:

	switch (token.type)
	{
		usize index;

		case TOKEN_KEYWORD_FUNCTION:
			if (!parseFunction(&index, &token, package))
			{
				success = false;
				break;
			}

			arrayPush(&node->functionIds, &index);
			goto parse;

		case TOKEN_KEYWORD_STRUCT:
			if (!parseStruct(&index, &token, package))
			{
				success = false;
				break;
			}

			arrayPush(&node->structIds, &index);
			goto parse;

		case TOKEN_END_OF_FILE:
			break;

		default:
			printParseError(&token, "type or function definition", NULL);
			success = false;
			break;
	}

	return success;
}

bool declareStruct(usize *index)
{
	return symbolTableDeclareGlobal(SYMBOL_STRUCT, *index);
}

bool declareFunction(usize *index)
{
	return symbolTableDeclareGlobal(SYMBOL_FUNCTION, *index);
}

bool declareModule(Module *module)
{
	bool success = true;

	if (!arrayForEach(&module->structIds, (ElementAction)declareStruct))
		success = false;

	if (!arrayForEach(&module->functionIds, (ElementAction)declareFunction))
		success = false;

	return success;
}

bool validateModule(Module *module, const Scope *packageScope)
{
	assert(module != NULL);
	assert(packageScope != NULL);

	bool success = true;
	IndexList *functionIds = &module->functionIds;
	IndexList *structIds = &module->structIds;
	LocalSymbolTable localTable = localSymbolTableCreate(packageScope);

	for (usize i = 0; i < functionIds->length; ++i)
	{
		Function *function = symbolTableGetFunction(functionIds->data[i]);

		localTable.function = function;

		if (!validateFunction(function, &localTable))
			success = false;

		localSymbolTableClear(&localTable);
	}

	for (usize i = 0; i < structIds->length; ++i)
	{
		Struct *node = symbolTableGetStruct(structIds->data[i]);

		if (!validateStruct(node, packageScope))
			success = false;
	}

	return success;
}

void moduleFree(Module *node)
{
	arrayDestroy(&node->functionIds, NULL);
	arrayDestroy(&node->structIds, NULL);

	deallocate(node->symbol);
}
