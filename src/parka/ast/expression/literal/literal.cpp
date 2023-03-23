#include "parka/ast/expression/literal.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/symbol_table.hpp"
#include "parka/util/print.hpp"

typedef usize (*LiteralValidationFunction)(const Primitive *);

Literal::Literal(Literal&& other)
{

}

Literal::~Literal()
{
	if (_type == LiteralType::String)
			_string.~basic_string();
}

Optional<Box<Expression>> parseCharacterLiteral(Token& token)
{
	if (token.length() != 3)
	{
		printTokenError(token, "character literals may only contain 1 character", NULL);
		return false;
	}

	auto character = token[0];
	auto expression = new Literal(

	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = (Literal)
	{
		.token = *token,
		.character = tokenGetChar(token, 1),
		.type = LiteralType::Character
	};

	token.increment();

	return true;
}

Optional<Box<Expression>> parseFloatLiteral(Token& token)
{
	// TODO: account for multiple decimals when parsing float

	f64 value = 0.0;
	for (usize i = 0; i < token.length(); ++i)
	{
		if (token[i] != '.')
		{
			value = value * 10.0 + (token[i] - '0');
		}
		else
		{
			i += 1;

			f64 decimal = 0.0;
			f64 place = 1.0;

			while (i < token.length())
			{
				decimal = decimal * 10.0 + (token[i] - '0');
				place *= 10.0;
				++i;
			}
			
			value += (decimal / place);
			break;
		}
	}
	


	auto expression = new Literal(value);

	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = (Literal)
	{
		.token = *token,
		.type = LiteralType::Float,
		.floating = value
	};

	token.increment();

	return true;
}

Optional<Box<Expression>> StringLiteral::parse(Token& token)
{
	Literal literal =
	{
		.token = *token,
		.string = { tokenGetText(token), token.length() },
		.type = LiteralType::String
	};

	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = literal;

	token.increment();

	return true;
}

Optional<Box<Expression>> IntegerLiteral::parse(Token& token)
{
	// TODO: Calculate required size for integers
	// TODO: Confirm will fit in required size

	u64 value = 0;

	for (usize i = 0; i < token.length(); ++i)
		value = value * 10 + (tokenGetChar(token, i) - '0');

	

	out->type = EXPRESSION_LITERAL;
	out->literal = new(Literal);
	*out->literal = (Literal)
	{
		*token,
		{ value },
		LiteralType::Integer
	};

	token.increment();
	
	return true;
}

Optional<Box<Expression>> BooleanLiteral::parse(Token& token)
{
	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = (Literal)
	{
		.type = LiteralType::Boolean,
		.token = *token,
		.boolean = token.type() == TokenType::KeywordTrue
	};

	token.increment();

	return true;
}

Optional<Box<Expression>> Literal::parse(Token& token)
{
	switch (token.type())
	{
		case TokenType::CharacterLiteral:
			return parseCharacterLiteral(out, token);

		case TokenType::StringLiteral:
			return parseStringLiteral(out, token);

		case TokenType::IntegerLiteral:
			return parseIntegerLiteral(out, token);

		case TokenType::FloatLiteral:
			return parseFloatLiteral(out, token);

		case TokenType::KeywordTrue:
		case TokenType::KeywordFalse:
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
		case LiteralType::Character:
			return getCharacterLiteralSymbolId;

		case LiteralType::String:
			return getStringLiteralSymboId;

		case LiteralType::Integer:
			return getIntegerLiteralSymbolId;

		case LiteralType::Float:
			return getFloatLiteralSymbolId;

		case LiteralType::Boolean:
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
		case LiteralType::Character:
			return "char literal";

		case LiteralType::String:
			return "string literal";
			
		case LiteralType::Integer:
			return "integer literal";

		case LiteralType::Float:
			return "float literal";

		case LiteralType::Boolean:
			return "bool literal";

		default:
            break;
	}

    exitWithErrorFmt("Unable to get name for LiteralType: %d.", type);
}

const Primitive *getTypePrimitive(const Type *type)
{
	if (type == NULL || type->type != EntityType::Primitive)
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
		.type = EntityType::Primitive
	};

	return true;
}
