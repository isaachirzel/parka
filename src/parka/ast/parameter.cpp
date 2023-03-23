#include "parka/ast/parameter.hpp"
#include "parka/symbol_table.hpp"

#include "parka/util/print.hpp"

bool parseParameter(Parameter *out, Token& token)
{
	*out = (Parameter) { 0 };

	if (token.type() == TokenType::KeywordMut)
	{
		out->isMutable = true;
		token.increment();
	}

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "parameter name", NULL);
		return false;
	}

	out->name = *token;
	out->symbol = tokenGetText(token);

	token.increment();

	if (token.type() != TokenType::Colon)
	{
		printParseError(token, ":", "parameters require a valid type");
		return false;
	}

	token.increment();

	if (!parseTypeAnnotation(&out->annotation, token))
		return false;
	
	return true;
}

bool parseParameterList(IndexList *out, Token& token)
{
	arrayInit(out, 3);

	if (token.type() != TokenType::LeftParenthesis)
	{
		printParseError(token, "'(' after function name", NULL);
		return false;
	}

	token.increment();

	if (token.type() != TokenType::RightParenthesis)
	{
		while (true)
		{
			usize index = symbolTableAddParameter();
			Parameter *parameter = symbolTableGetParameter(index);

			if (!parseParameter(parameter, token))
				return false;

			arrayPush(out, &index);

			if (token.type() != TokenType::Comma)
				break;

			token.increment();
		}

		if (token.type() != TokenType::RightParenthesis)
		{
			printParseError(token, "')'", "Invalid tokens in parameter list");
			return false;
		}
	}

	token.increment();

	return true;
}

bool validateParameter(Parameter *node, SymbolTable& localTable)
{	
	if (!validateTypeAnnotation(&node->annotation, localTable->packageScope))
		return false;

	return true;
}

bool validateParameterList(const IndexList *ids, SymbolTable& localTable)
{
	bool success = true;

	for (usize i = 0; i < ids->length; ++i)
	{
		usize index = ids->data[i];

		if (!symbolTableDeclareLocal(localTable, EntityType::Parameter, index))
			success = false;

		Parameter *node = symbolTableGetParameter(index);

		if (!validateParameter(node, localTable))
			success = false;
	}

	return success;
}
