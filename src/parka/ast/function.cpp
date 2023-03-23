#include "parka/ast/function.hpp"
#include "parka/ast/expression/block.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/ast/parameter.hpp"
#include "parka/symbol_table.hpp"
#include "parka/util/array.hpp"

#include "parka/util/print.hpp"

bool parseFunction(usize *out, Token& token, const String& package)
{
	assert(token.type() == TokenType::KeywordFunction);

	usize index = symbolTableAddFunction();
	Function *node = symbolTableGetFunction(index);

	token.increment();

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "function name", NULL);
		return false;
	}

	node->name = *token;
	node->symbol = createSymbolKey(package, token);

	token.increment();

	if (!parseParameterList(&node->parameterIds, token))
		return false;

	if (token.type() == TokenType::Colon)
	{
		token.increment();

		if (!parseTypeAnnotation(&node->returnType, token))
			return false;

		node->hasReturnType = true;
	}

	if (token.type() != TokenType::LeftBrace)
	{
		printParseError(token, "'{' after function signature", NULL);
		return false;
	}

	if (!parseBlock(&node->body, token))
		return false;

	*out = index;

	return true;
}

bool validateFunction(Function *node, SymbolTable& localTable)
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
			auto returnTypeName = typeGetName(returnType);
			auto bodyTypeName = typeGetName(&bodyType);
			// TODO: handle token like so: Token token = tokenFromExpression(&node->body);

			printError("Expected `%s`, got `%s`.", returnTypeName, bodyTypeName);
			printTokenNote(&node->returnType.token, "Function return type here.");

			success = false;
		}
	}	

	return success;
}

const Type *functionGetReturnType(const Function *function)
{
	const Type *returnType = function->hasReturnType
		? &function->returnType.type
		: &voidType;

	return returnType;
}
