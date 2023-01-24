#include "warbler/ast/expression/identifier.h"
#include "warbler/ast/expression/expression.h"
#include "warbler/ast/parameter.h"
#include "warbler/ast/type.h"
#include "warbler/ast/variable.h"
#include "warbler/symbol.h"
#include "warbler/symbol_table.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"

bool parseIdentifier(Expression *out, Token *token)
{
	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "symbol", NULL);
		return false;
	}

	incrementToken(token);

	*out = (Expression)
	{
		.type = EXPRESSION_IDENTIFIER
	};

	*makeNew(out->identifier) = (Identifier)
	{
		.token = *token
	};

	return true;
}

bool validateIdentifier(Identifier *node, LocalSymbolTable *localTable)
{
	assert(node != NULL);
	assert(localTable != NULL);

	const Symbol *symbol = symbolTableResolve(localTable, &node->token);

	if (!symbol)
		return false;

	switch (symbol->type)
	{
		case SYMBOL_PACKAGE:
		case SYMBOL_STRUCT:
			printTokenError
			(
				&node->token,
				"Expected identifier, found %s `%s`.",
				symbolTypeName(symbol->type),
				symbol->key
			);
			return false;

		default:
			break;
	}
	
	node->index = symbol->index;
	node->type = symbol->type;

	return true;
}

bool identifierGetType(Type *out, Identifier *node, const Type *expected)
{
	switch (node->type)
	{
		// case SYMBOL_FUNCTION: // TODO: Add function primitive
		case SYMBOL_VARIABLE:
		{
			Variable *variable = symbolTableGetVariable(node->index);

			*out = typeDuplicate(&variable->annotation.type);

			return true;
		}
		
		case SYMBOL_PARAMETER:
		{
			Parameter *parameter = symbolTableGetParameter(node->index);

			*out = typeDuplicate(&parameter->annotation.type);

			return true;
		}

		default:
			break;
	}

	exitWithErrorFmt("Unable to get Type for Identifier with SymbolType: %d.", node->type);
}
