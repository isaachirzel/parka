#include "warbler/ast/type.h"
#include "warbler/ast/expression/additive.h"
#include "warbler/ast/expression/literal.h"
#include "warbler/ast/function.h"
#include "warbler/ast/primitive.h"
#include "warbler/symbol.h"
#include "warbler/symbol_table.h"
#include "warbler/util/print.h"

const Type voidType = { INDEX_VOID, SYMBOL_PRIMITIVE };
const Type i32Type = { INDEX_I32, SYMBOL_PRIMITIVE };

void typeFree(Type *type)
{
	assert(type);
	// TODO: pointers
}

bool parseTypeAnnotation(TypeAnnotation *out, Token *token)
{
	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "type", NULL);
		return false;
	}
	
	out->token = *token;

	incrementToken(token);

	return true;
}

bool validateTypeAnnotation(TypeAnnotation *node, const Scope *packageScope)
{
	assert(node != NULL);
	assert(packageScope != NULL);

	const Token *token = &node->token;
	Symbol *symbol = symbolTableResolveGlobal(packageScope, token);

	if (!symbol)
		return false;

	switch (symbol->type)
	{
		case SYMBOL_STRUCT:
		case SYMBOL_PRIMITIVE:
			node->type = (Type)
			{
				.type = symbol->type,
				.index = symbol->index
			};

			return true;

		default:
			break;
	}

	const char *typeName = symbolTypeGetName(symbol->type);

	printTokenError(token, "Expected type name, found %s.", typeName);

	return false;
}

void typeAnnotationFree(TypeAnnotation *node)
{
	typeFree(&node->type);
}

char *typeGetName(const Type *type)
{
	Symbol *symbol = symbolTableGetSymbol(type->index);
	char *name = stringDuplicate(symbol->key);

	return name;
}

bool typeCanConvert(const Type *to, const Type *from)
{
	bool canConvert = to->type == from->type
		&& to->index == from->index;

	return canConvert;
}

Type typeDuplicate(const Type *type)
{
	return *type;
}
