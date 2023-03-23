#include "parka/ast/module.hpp"
#include "parka/ast/function.hpp"
#include "parka/ast/struct.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"

#include "parka/util/print.hpp"

bool parseModule(Module *node, const File *file, const String& package)
{
	printFmt("Parsing file: %s", file->path);
	// TODO: parse error recovery
	bool success = true;
	Token token = getInitialToken(file);

	arrayInit(&node->functionIds, 5);
	arrayInit(&node->structIds, 2);

parse:

	switch (token.type)
	{
		usize index;

		case TokenType::KeywordFunction:
			if (!parseFunction(&index, &token, package))
			{
				success = false;
				break;
			}

			arrayPush(&node->functionIds, &index);
			goto parse;

		case TokenType::KeywordStruct:
			if (!parseStruct(&index, &token, package))
			{
				success = false;
				break;
			}

			arrayPush(&node->structIds, &index);
			goto parse;

		case TokenType::EndOfFile:
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
	return symbolTableDeclareGlobal(EntityType::Struct, *index);
}

bool declareFunction(usize *index)
{
	return symbolTableDeclareGlobal(EntityType::Function, *index);
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
	print("Validating module");
	assert(module != NULL);
	assert(packageScope != NULL);

	bool success = true;
	IndexList *functionIds = &module->functionIds;
	IndexList *structIds = &module->structIds;
	SymbolTable localTable = localSymbolTableCreate(packageScope);

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
