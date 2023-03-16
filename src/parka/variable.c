#include "parka/ast/variable.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseVariable(Variable *out, Token *token)
{
	assert(token->type == TOKEN_KEYWORD_VAR);

	Variable node = { 0 };

	incrementToken(token);

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "variable name", NULL);
		return false;
	}

	node.name = *token;
	node.symbol = tokenGetText(token);

	incrementToken(token);

	if (token->type != TOKEN_COLON)
	{
		*out = node;
		return true;
	}
	
	incrementToken(token);

	node.isExplicitlyTyped = true;

	if (!parseTypeAnnotation(&node.annotation, token))
		goto error;

	*out = node;
	return true;

error:

	variableFree(&node);
	return false;
}

bool validateVariable(Variable *node, LocalSymbolTable *localTable)
{
	if (node->isExplicitlyTyped)
		return validateTypeAnnotation(&node->annotation, localTable->packageScope);

	return true;
}

void variableFree(Variable *node)
{
	typeAnnotationFree(&node->annotation);
	deallocate(node->symbol);
}
