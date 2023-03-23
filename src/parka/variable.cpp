#include "parka/ast/variable.hpp"

#include "parka/util/print.hpp"

Optional<Variable> Variable::parse(Token& token)
{
	assert(token.type() == TokenType::KeywordVar);

	Variable node = { 0 };

	token.increment();

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "variable name", NULL);
		return false;
	}

	node.name = *token;
	node.symbol = tokenGetText(token);

	token.increment();

	if (token.type() != TokenType::Colon)
	{
		*out = node;
		return true;
	}
	
	token.increment();

	node.isExplicitlyTyped = true;

	if (!parseTypeAnnotation(&node.annotation, token))
		goto error;

	*out = node;
	return true;

error:

	variableFree(&node);
	return false;
}

bool validateVariable(Variable *node, LocalEntityTable& localTable)
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
