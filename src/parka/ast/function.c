#include "parka/ast/function.h"
#include "parka/ast/expression/block.h"
#include "parka/ast/expression/expression.h"
#include "parka/ast/parameter.h"
#include "parka/symbol_table.h"
#include "parka/util/array.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseFunction(usize *out, Token *token, const char *package)
{
	assert(token->type == TOKEN_KEYWORD_FUNCTION);

	usize index = symbolTableAddFunction();
	Function *node = symbolTableGetFunction(index);

	incrementToken(token);

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "function name", NULL);
		return false;
	}

	node->name = *token;
	node->symbol = createSymbol(package, token);

	incrementToken(token);

	if (!parseParameterList(&node->parameterIds, token))
		return false;

	if (token->type == TOKEN_COLON)
	{
		incrementToken(token);

		if (!parseTypeAnnotation(&node->returnType, token))
			return false;

		node->hasReturnType = true;
	}

	if (token->type != TOKEN_LEFT_BRACE)
	{
		printParseError(token, "'{' after function signature", NULL);
		return false;
	}

	if (!parseBlock(&node->body, token))
		return false;

	*out = index;

	return true;
}

bool validateFunction(Function *node, LocalSymbolTable *localTable)
{
	bool success = true;

	if (!validateParameterList(&node->parameterIds, localTable))
		success = false;

	if (node->hasReturnType
			&& !validateTypeAnnotation(&node->returnType, localTable->packageScope))
		success = false;

	if (!validateExpression(&node->body, localTable))
		success = false;

	if (success)
	{
		const Type *returnType = functionGetReturnType(node);
		Type bodyType;
		
		if (!expressionGetType(&bodyType, &node->body, returnType))
			return false;

		if (!typeCanConvert(returnType, &bodyType))
		{
			char *returnTypeName = typeGetName(returnType);
			char *bodyTypeName = typeGetName(&bodyType);
			// TODO: handle token like so: Token token = tokenFromExpression(&node->body);

			printError("Expected `%s`, got `%s`.", returnTypeName, bodyTypeName);
			printTokenNote(&node->returnType.token, "Function return type here.");
			deallocate(returnTypeName);
			deallocate(bodyTypeName);

			success = false;
		}
	}	

	return success;
}

void functionFree(Function *node)
{
	expressionFree(&node->body);
	arrayDestroy(&node->parameterIds, NULL);

	if (node->hasReturnType)
		typeAnnotationFree(&node->returnType);

	deallocate(node->symbol);
}

const Type *functionGetReturnType(const Function *function)
{
	const Type *returnType = function->hasReturnType
		? &function->returnType.type
		: &voidType;

	return returnType;
}
