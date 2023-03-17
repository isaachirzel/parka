#include "parka/ast/expression/block.h"
#include "parka/ast/statement/statement.h"
#include "parka/parser.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseBlock(Expression *out, Token *token)
{
	assert(token->type == TOKEN_LEFT_BRACE);

	incrementToken(token);

	Block node = { 0 };

	while (true)
	{
		if (token->type == TOKEN_RIGHT_BRACE)
			break;

		if (token->type == TOKEN_END_OF_FILE)
		{
			printParseError(token, "'}'", NULL);
			return false;
		}

		Statement statement = { 0 };

		if (!parseStatement(&statement, token))
			goto error;

		resizeArray(node.statements, ++node.count);
		node.statements[node.count - 1] = statement;
	}

	incrementToken(token);

	*makeNew(out->block) = node;
	out->type = EXPRESSION_BLOCK;

	return true;

error:

	blockFree(&node);
	return false;
}

bool validateBlock(Block *node, LocalSymbolTable *localTable)
{
	assert(node != NULL);
	assert(localTable != NULL);

	bool success = true;

	print("Validating block");

	localSymbolTablePushBlock(localTable, node);

	for (usize i = 0; i < node->count; ++i)
	{
		printFmt("Validating statement: %zu", i);
		if (!validateStatement(&node->statements[i], localTable))
			success = false;
	}

	localSymbolTablePopBlock(localTable);

	return success;
}

void blockFree(Block *node)
{
	for (usize i = 0; i< node->count; ++i)
		statementFree(&node->statements[i]);
}

bool blockGetType(Type *out, Block *block, const Type *expected)
{
	*out = block->hasReturnType
		? typeDuplicate(&block->returnType)
		: typeDuplicate(&voidType);

	return true;
}
