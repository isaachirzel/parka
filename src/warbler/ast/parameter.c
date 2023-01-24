#include "warbler/ast/parameter.h"
#include "warbler/symbol_table.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"

bool parseParameter(Parameter *out, Token *token)
{
	*out = (Parameter) { 0 };

	if (token->type == TOKEN_KEYWORD_MUT)
	{
		out->isMutable = true;
		incrementToken(token);
	}

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "parameter name", NULL);
		return false;
	}

	out->name = *token;
	out->symbol = tokenGetText(token);

	incrementToken(token);

	if (token->type != TOKEN_COLON)
	{
		printParseError(token, ":", "parameters require a valid type");
		return false;
	}

	incrementToken(token);

	if (!parseTypeAnnotation(&out->annotation, token))
		return false;
	
	return true;
}

bool parseParameterList(IndexList *out, Token *token)
{
	arrayInit(out, 3);

	if (token->type != TOKEN_LEFT_PARENTHESIS)
	{
		printParseError(token, "'(' after function name", NULL);
		return false;
	}

	incrementToken(token);

	if (token->type != TOKEN_RIGHT_PARENTHESIS)
	{
		while (true)
		{
			usize index = symbolTableAddParameter();
			Parameter *parameter = symbolTableGetParameter(index);

			if (!parseParameter(parameter, token))
				return false;

			arrayPush(out, &index);

			if (token->type != TOKEN_COMMA)
				break;

			incrementToken(token);
		}

		if (token->type != TOKEN_RIGHT_PARENTHESIS)
		{
			printParseError(token, "')'", "Invalid tokens in parameter list");
			return false;
		}
	}

	incrementToken(token);

	return true;
}

bool validateParameter(Parameter *node, LocalSymbolTable *localTable)
{	
	if (!validateTypeAnnotation(&node->annotation, localTable->packageScope))
		return false;

	return true;
}

bool validateParameterList(const IndexList *ids, LocalSymbolTable *localTable)
{
	bool success = true;

	for (usize i = 0; i < ids->length; ++i)
	{
		usize index = ids->data[i];

		if (!symbolTableDeclareLocal(localTable, SYMBOL_PARAMETER, index))
			success = false;

		Parameter *node = symbolTableGetParameter(index);

		if (!validateParameter(node, localTable))
			success = false;
	}

	return success;
}

void parameterFree(Parameter *node)
{
	typeAnnotationFree(&node->annotation);
	deallocate(node->symbol);
}
