#include <warbler/ast/constant.h>

// standard headers
#include <assert.h>
#include <stdlib.h>

void constant_init(Constant *constant)
{
	assert(constant != NULL);

	constant->type = CONSTANT_INTEGER;
	constant->integer = 0;
}

void constant_free(Constant *constant)
{
	assert(constant != NULL);

	if (constant->type == CONSTANT_STRING)
		free(constant->string);
}

static inline u32 parse_character(const char *text)
{
	#pragma message "Make sure character literals are only 1 long"
	return 0;
}

static double parse_float(const String *text, bool is_negative)
{
	double out = 0.0;

	const char * restrict data = text->data;
	size_t length = text->length;

	for (size_t i = 0; i < length; ++i)
	{
		if (data[i] != '.')
		{
			out = out * 10.0 + (data[i] - '0');
		}
		else
		{
			double decimal = 0.0;
			double place = 1.0;

			while (i < length)
			{
				decimal = decimal * 10.0 + (data[i] - '0');
				place *= 10.0;
				++i;
			}
			
			out += (decimal / place);
			break;
		}
	}

	if (is_negative)
		out = -out;
	
	return out;
}

static i64 parse_int(const String *text, bool is_negative)
{
	i64 out = 0;

	const char * restrict data = text->data;
	size_t length = text->length;

	for (size_t i = 0; i < length; ++i)
		out = out * 10 + (data[i] - '0');

	if (is_negative)
		out = -out;

	return out;
}

static inline Error parse_number(Constant *self, TokenIterator *iter, bool is_negative)
{
	switch (iter->token->type)
	{
		case TOKEN_INTEGER_LITERAL:
			self->type = CONSTANT_INTEGER;
			self->integer = parse_int(&iter->token->string, is_negative);
			break;

		case TOKEN_FLOAT_LITERAL:
			self->type = CONSTANT_FLOAT;
			self->float64 = parse_float(&iter->token->string, is_negative);
			break;

		default:
			print_error("expected number literal but got: ");
			string_println(&iter->token->string);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

static inline Error try_constant_parse(Constant *self, TokenIterator *iter)
{
	Error error;

	switch (iter->token->type)
	{
		case TOKEN_MINUS:
			++iter->token;
			if ((error = parse_number(self, iter, true)))
				return error;
			break;

		case TOKEN_PLUS:
			++iter->token;
			if ((error = parse_number(self, iter, false)))
				return error;
			break;

		case TOKEN_INTEGER_LITERAL:
			self->type = CONSTANT_INTEGER;
			self->integer = parse_int(&iter->token->string, false);
			break;

		case TOKEN_FLOAT_LITERAL:
			self->type = CONSTANT_FLOAT;
			self->float64 = parse_float(&iter->token->string, false);
			break;

		case TOKEN_HEXADECIMAL_LITERAL:
			return not_implemented_error();
			break;

		case TOKEN_BINARY_LITERAL:
			return not_implemented_error();
			break;

		case TOKEN_OCTAL_LITERAL:
			return not_implemented_error();
			break;

		case TOKEN_CHAR_LITERAL:
			return not_implemented_error();
			break;

		case TOKEN_STRING_LITERAL:
			self->type = CONSTANT_STRING;
			self->string = string_duplicate(&iter->token->string);

			if (!self->string)
				return ERROR_MEMORY;
			break;

		case TOKEN_TRUE:
			break;

		case TOKEN_FALSE:
			break;

		default:
			print_error("expected constant but got: ");
			string_println(&iter->token->string);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

Error constant_parse(Constant *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	constant_init(self);

	puts("Constant");
	Error error = try_constant_parse(self, iter);

	if (self->type == CONSTANT_INTEGER)
	{
		printf("Got integer: %ld\n", self->integer);
	}

	if (error)
		constant_free(self);

	return error;
}
