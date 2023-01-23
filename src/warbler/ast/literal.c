#include "warbler/ast/literal.h"
#include "warbler/ast/primitive.h"
#include "warbler/ast/type.h"
#include "warbler/symbol_table.h"
#include "warbler/util/print.h"

typedef usize (*LiteralValidationFunction)(const Primitive *);

void stringLiteralFree(StringLiteral *node)
{
	deallocate(node->text);
}

void literalFree(Literal *node)
{
	if (node->type == LITERAL_STRING)
		stringLiteralFree(&node->string);
}

usize getFloatLiteralSymbolId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_FLOATING_POINT)
		return NOT_FOUND;

	return INDEX_F64;
}

usize getIntegerLiteralSymbolId(const Primitive *primitive)
{
	if (primitive)
	{
		switch (primitive->type)
		{
			// TODO: Add boolean and char
			case PRIMITIVE_UNSIGNED_INTEGER:
			case PRIMITIVE_SIGNED_INTEGER:
			case PRIMITIVE_FLOATING_POINT:
				return NOT_FOUND;

			default:
				break;
		}
	}

	return INDEX_I32;
}

usize getBooleanLiteralSymbolId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_BOOLEAN)
		return NOT_FOUND;

	return INDEX_BOOL;
}

usize getCharacterLiteralSymbolId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_CHARACTER)
		return NOT_FOUND;

	return INDEX_CHAR;
}

usize getStringLiteralSymboId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_STRING)
		return NOT_FOUND;

	return INDEX_STRING;
}

LiteralValidationFunction getLiteralValidationFunction(Literal *literal)
{
	switch (literal->type)
	{
		case LITERAL_CHARACTER:
			return getCharacterLiteralSymbolId;

		case LITERAL_STRING:
			return getStringLiteralSymboId;

		case LITERAL_INTEGER:
			return getIntegerLiteralSymbolId;

		case LITERAL_FLOAT:
			return getFloatLiteralSymbolId;

		case LITERAL_BOOLEAN:
			return getBooleanLiteralSymbolId;

		default:
			break;
	}

	exitWithErrorFmt("Unable to get SymbolId for Literal of type: %d", literal->type);
}

const char *literalTypeName(LiteralType type)
{
	switch (type)
	{
		case LITERAL_CHARACTER:
			return "char literal";

		case LITERAL_STRING:
			return "string literal";
			
		case LITERAL_INTEGER:
			return "integer literal";

		case LITERAL_FLOAT:
			return "float literal";

		case LITERAL_BOOLEAN:
			return "bool literal";

		default:
            break;
	}

    exitWithErrorFmt("Unable to get name for LiteralType: %d.", type);
}

static const Primitive *getTypePrimitive(const Type *type)
{
	if (type == NULL || type->type != SYMBOL_PRIMITIVE)
		return NULL;

	const Primitive *primitive = symbolTableGetPrimitive(type->index);

	return primitive;
}

usize getLiteralSymbolId(Literal *literal, const Type *expectedType)
{
	assert(literal != NULL);

	LiteralValidationFunction check = getLiteralValidationFunction(literal);
	const Primitive *primitive = getTypePrimitive(expectedType);
	usize index = check(primitive);

	if (index == NOT_FOUND)
		index = expectedType->index;

	return index;
}

Type literalGetType(Literal *literal, const Type *expectedType)
{
	// TODO: Make this not always a primitive, because there are literal structs

	Type type =
	{
		.index = getLiteralSymbolId(literal, expectedType),
		.type = SYMBOL_PRIMITIVE
	};

	return type;
}
