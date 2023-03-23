#include "parka/ast/statement/jump.hpp"
#include "parka/ast/expression/block.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/parser.hpp"
#include "parka/symbol_table.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/print.hpp"

Optional<JumpType> getJumpType(Token& token)
{
	switch (token.type())
	{
		case TokenType::KeywordReturn:
			return JUMP_RETURN;

		case TokenType::KeywordBreak:
			return JUMP_BREAK;

		case TokenType::KeywordContinue:
			return JUMP_CONTINUE;

		case TokenType::KeywordYield:
			return JUMP_YIELD;

		default:
			printParseError(token, "return, break, continue or yield", NULL);
			return {};
	}
}

Optional<JumpStatement> JumpStatement::parse(Token& token)
{
	auto type = getJumpType(token);

	if (!type)
		return {};

	auto t = token;

	token.increment();

	if (token.type() == TokenType::Semicolon)
	{
		token.increment();

		auto statement = JumpStatement(token, type.unwrap());

		return statement;
	}

	switch (type.value())
	{
		case JUMP_CONTINUE:
			// TODO: Implement continuing on labels
			printTokenError(token, "Continue statements cannot have a value.");
			return {};
		
		case JUMP_BREAK:
			printTokenError(token, "Break statements cannot have a value.");
			return {};

		default:
			break;
	}
	
	auto value = Expression::parse(token);

	if (!value)
		return {};
	
	if (token.type() != TokenType::Semicolon)
	{
		printParseError(token, "';' after jump statement", NULL);
		return {};
	}

	token.increment();

	auto statement = JumpStatement(token, type.unwrap(), value.unwrap());

	return statement;
}

bool validateReturnStatement(JumpStatement *node, SymbolTable& localTable)
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

bool validateYieldStatement(JumpStatement *node, SymbolTable& localTable)
{
	Block *currentBlock = localSymbolTableGetCurrentBlock(localTable);

	if (currentBlock == NULL)
	{
		printTokenError(&node->token, "Yield statement must be within a block.");

		return false;
	}

	const auto& blockReturnType = currentBlock->hasReturnType
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
		auto blockTypeName = blockReturnType.getName();
		// TODO: get type token

		printError("Yield value is not compatible with type of block expression `%s`.", blockTypeName);

		return false;
	}

	return true;
}

bool JumpStatement::validate(SymbolTable& localTable)
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
