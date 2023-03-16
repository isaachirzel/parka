#include "parka/ast/statement/jump.h"
#include "parka/ast/expression/block.h"
#include "parka/ast/expression/expression.h"
#include "parka/ast/function.h"
#include "parka/parser.h"
#include "parka/symbol_table.h"
#include "parka/util/print.h"

bool parseJumpStatement(JumpStatement *out, Token *token)
{
	switch (token->type)
	{
		case TOKEN_KEYWORD_RETURN:
			out->type = JUMP_RETURN;
			break;

		case TOKEN_KEYWORD_BREAK:
			out->type = JUMP_BREAK;
			break;

		case TOKEN_KEYWORD_CONTINUE:
			out->type = JUMP_CONTINUE;
			break;

		case TOKEN_KEYWORD_YIELD:
			out->type = JUMP_YIELD;
			break;

		default:
			printParseError(token, "return, break, continue or yield", NULL);
			return false;
	}

	out->token = *token;

	incrementToken(token);

	if (token->type == TOKEN_SEMICOLON)
	{
		incrementToken(token);
		return true;
	}

	switch (out->type)
	{
		case JUMP_CONTINUE:
			// TODO: Implement continuing on labels
			printTokenError(token, "Continue statements cannot have a value.");
			return false;
		
		case JUMP_BREAK:
			printTokenError(token, "Break statements cannot have a value.");
			return false;

		default:
			break;
	}

	out->hasValue = true;
	
	if (!parseExpression(&out->value, token))
		return false;
	
	if (token->type != TOKEN_SEMICOLON)
	{
		printParseError(token, "';' after jump statement", NULL);
		return false;
	}

	incrementToken(token);
	return true;
}

bool validateReturnStatement(JumpStatement *node, LocalSymbolTable *localTable)
{
	if (node->hasValue && !validateExpression(&node->value, localTable))
		return false;

	Function *function = localTable->function;
	const Type *returnType = functionGetReturnType(function);

	Type valueType;
	
	if (node->hasValue)
	{
		if (!expressionGetType(&valueType, &node->value, returnType))
			return false;
	}
	else
	{
		valueType = typeDuplicate(&voidType);
	}
	
	Expression *functionBody = &function->body;

	if (functionBody->type == EXPRESSION_BLOCK)
	{
		Block *block = functionBody->block;

		block->returnType = typeDuplicate(&valueType);
		block->hasReturnType = true;
	}

	if (!typeCanConvert(returnType, &valueType))
	{
		char *returnTypeName = typeGetName(returnType);

		printError("Return value is not compatible with return type `%s`.", returnTypeName);
		deallocate(returnTypeName);

		return false;
	}

	return true;
}

bool validateYieldStatement(JumpStatement *node, LocalSymbolTable *localTable)
{
	Block *currentBlock = localSymbolTableGetCurrentBlock(localTable);

	if (currentBlock == NULL)
	{
		printTokenError(&node->token, "Yield statement must be within a block.");

		return false;
	}

	const Type *blockReturnType = currentBlock->hasReturnType
		? &currentBlock->returnType
		: &voidType;
	// TODO: Confirm copying type is OK
	Type valueType;
	
	if (node->hasValue)
	{
		if (!expressionGetType(&valueType, &node->value, blockReturnType))
			return false;
	}
	else
	{
		valueType = typeDuplicate(&voidType);
	}

	if (typeCanConvert(blockReturnType, &valueType))
	{
		const char *blockTypeName = typeGetName(blockReturnType);
		// TODO: get type token

		printError("Yield value is not compatible with type of block expression `%s`.", blockTypeName);

		return false;
	}

	return true;
}

bool validateJumpStatement(JumpStatement *node, LocalSymbolTable *localTable)
{
	switch (node->type)
	{
		case JUMP_RETURN:
			return validateReturnStatement(node, localTable);

		case JUMP_BREAK:
			break;

		case JUMP_CONTINUE:
			break;

		case JUMP_YIELD:
			return validateYieldStatement(node, localTable);

		default:
			break;
	}
	
	exitWithErrorFmt("Unable to validate JumpStatement with type: %d", node->type);
}

void jumpStatementFree(JumpStatement *node)
{
	if (node->hasValue)
		expressionFree(&node->value);
}
