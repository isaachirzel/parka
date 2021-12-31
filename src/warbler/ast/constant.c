#include <warbler/ast/constant.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <assert.h>
#include <stdlib.h>

void constant_init(Constant *self)
{
	assert(self);

	self->type = CONSTANT_INTEGER;
	self->integer = 0;
}

void constant_free(Constant *self)
{
	if (!self)
		return;

	if (self->type == CONSTANT_STRING)
		free(self->string);
}

static inline u32 parse_character(const char *text)
{
	#pragma message "Make sure character literals are only 1 long"
	return 0;
}

static f64 string_to_f64(const String *text)
{
	f64 out = 0.0;

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
			f64 decimal = 0.0;
			f64 place = 1.0;

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
	
	return out;
}

static i64 string_to_i64(const String *text)
{
	i64 out = 0;

	const char * restrict data = text->data;
	size_t length = text->length;

	for (size_t i = 0; i < length; ++i)
		out = out * 10 + (data[i] - '0');

	return out;
}

static inline void parse_integer_literal(Constant *self, TokenIterator *iter, bool is_negative)
{
	i64 value = string_to_i64(&iter->token->text);

	self->type = CONSTANT_INTEGER;
	self->integer = is_negative
		? -value
		: value;

	++iter->token;
}

static inline void parse_float_literal(Constant *self, TokenIterator *iter, bool is_negative)
{
	f64 value = string_to_f64(&iter->token->text);

	self->type = CONSTANT_FLOAT;
	self->float64 = is_negative
		? -value
		: value;

	++iter->token;
}

static inline Error parse_number(Constant *self, TokenIterator *iter, bool is_negative)
{
	switch (iter->token->type)
	{
		case TOKEN_INTEGER_LITERAL:
			parse_integer_literal(self, iter, is_negative);
			break;

		case TOKEN_FLOAT_LITERAL:
			parse_float_literal(self, iter, is_negative);
			break;

		default:
			print_error("expected number literal but got: ");
			string_println(&iter->token->text);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

Error constant_parse(Constant *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	constant_init(self);

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
			parse_integer_literal(self, iter, false);
			break;

		case TOKEN_FLOAT_LITERAL:
			parse_float_literal(self, iter, false);
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
			self->string = string_duplicate(&iter->token->text);

			if (!self->string)
				return ERROR_MEMORY;
			break;

		case TOKEN_TRUE:
			break;

		case TOKEN_FALSE:
			break;

		default:
			print_error("expected constant but got: ");
			string_println(&iter->token->text);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

void constant_print_tree(Constant *self, unsigned depth)
{
	assert(self);

	print_branch(depth);

	switch (self->type)
	{
		case CONSTANT_CHAR:
			assert(false && "character print is not implemented");
			break;

		case CONSTANT_STRING:	
			puts(self->string);
			break;

		case CONSTANT_INTEGER:
			printf("%ld\n", self->integer);
			break;

		case CONSTANT_FLOAT:
			printf("%f\n", self->float64);
			break;
	}
}
