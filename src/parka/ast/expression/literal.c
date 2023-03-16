#include "parka/ast/expression/literal.h"
#include "parka/ast/primitive.h"
#include "parka/ast/type.h"
#include "parka/symbol_table.h"
#include "parka/util/print.h"

typedef usize (*LiteralValidationFunction)(const Primitive *);

static bool parseCharacterLiteral(Expression *out, Token *token)
{
	if (token->length != 3)
	{
		printTokenError(token, "character literals may only contain 1 character", NULL);
		return false;
	}

	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = (Literal)
	{
		.token = *token,
		.character = tokenGetChar(token, 1),
		.type = LITERAL_CHARACTER
	};

	incrementToken(token);

	return true;
}

static bool parseFloatLiteral(Expression *out, Token *token)
{
	// TODO: account for multiple decimals when parsing float

	f64 value = 0.0;
	for (usize i = 0; i < token->length; ++i)
	{
		if (tokenGetChar(token, i) != '.')
		{
			value = value * 10.0 + (tokenGetChar(token, i) - '0');
		}
		else
		{
			i += 1;

			f64 decimal = 0.0;
			f64 place = 1.0;

			while (i < token->length)
			{
				decimal = decimal * 10.0 + (tokenGetChar(token, i) - '0');
				place *= 10.0;
				++i;
			}
			
			value += (decimal / place);
			break;
		}
	}
	
	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = (Literal)
	{
		.token = *token,
		.type = LITERAL_FLOAT,
		.floating = value
	};

	incrementToken(token);

	return true;
}

static bool parseStringLiteral(Expression *out, Token *token)
{
	Literal literal =
	{
		.token = *token,
		.string = { tokenGetText(token), token->length },
		.type = LITERAL_STRING
	};

	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = literal;

	incrementToken(token);

	return true;
}

static bool parseIntegerLiteral(Expression *out, Token *token)
{
	// TODO: Calculate required size for integers
	// TODO: Confirm will fit in required size

	u64 value = 0;

	for (usize i = 0; i < token->length; ++i)
		value = value * 10 + (tokenGetChar(token, i) - '0');

	

	out->type = EXPRESSION_LITERAL;
	out->literal = new(Literal);
	*out->literal = (Literal)
	{
		*token,
		{ value },
		LITERAL_INTEGER
	};

	incrementToken(token);
	
	return true;
}

bool parseBooleanLiteral(Expression *out, Token *token)
{
	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = (Literal)
	{
		.type = LITERAL_BOOLEAN,
		.token = *token,
		.boolean = token->type == TOKEN_KEYWORD_TRUE
	};

	incrementToken(token);

	return true;
}

bool parseLiteral(Expression *out, Token *token)
{
	switch (token->type)
	{
		case TOKEN_CHARACTER_LITERAL:
			return parseCharacterLiteral(out, token);

		case TOKEN_STRING_LITERAL:
			return parseStringLiteral(out, token);

		case TOKEN_INTEGER_LITERAL:
			return parseIntegerLiteral(out, token);

		case TOKEN_FLOAT_LITERAL:
			return parseFloatLiteral(out, token);

		case TOKEN_KEYWORD_TRUE:
		case TOKEN_KEYWORD_FALSE:
			return parseBooleanLiteral(out, token);

		default:
			printParseError(token, "literal", NULL);
			return false;
	}
}

bool validateLiteral(Literal *node)
{
	assert(node != NULL);

	return true;
}

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

bool literalGetType(Type *out, Literal *literal, const Type *expected)
{
	// TODO: Make this not always a primitive, because there are literal structs

	*out = (Type)
	{
		.index = getLiteralSymbolId(literal, expected),
		.type = SYMBOL_PRIMITIVE
	};

	return true;
}
