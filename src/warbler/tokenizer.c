#include <warbler/tokenizer.h>

// local includes
#include <warbler/error.h>

// standard library
#include <string.h>
#include <stdlib.h>

// external libraries
#include <hirzel/table.h>
#include <hirzel/array.h>

typedef enum CharType
{
	CHAR_INVALID,
	CHAR_IDENTIFIER,
	CHAR_SEPARATOR,
	CHAR_DOT,
	CHAR_DIGIT,
	CHAR_OPERATOR,
	CHAR_QUOTE
} CharType;

typedef struct SourceLocation
{
	const char *pos;
	size_t line;
	size_t col;
} SourceLocation;

static inline SourceLocation source_location_create(const char *pos)
{
	return (SourceLocation) {
		.pos = pos,
		.line = 1,
		.col = 1
	};
}

typedef struct TokenInfo
{
	const char *key;
	TokenType value;
} TokenInfo;

const TokenInfo token_info[] =
{
	// misc keywords
	{ "func", TOKEN_FUNC },
	{ "var", TOKEN_VAR },
	{ "type", TOKEN_TYPE },
	{ "return", TOKEN_RETURN },
	{ "for", TOKEN_FOR },
	{ "while", TOKEN_WHILE },
	{ "loop", TOKEN_LOOP },
	{ "continue", TOKEN_CONTINUE },
	{ "break", TOKEN_BREAK },
	{ "if", TOKEN_IF },
	{ "else", TOKEN_ELSE },
	{ "switch", TOKEN_SWITCH },
	{ "case", TOKEN_CASE },

	// typenames
	{ "struct", TOKEN_STRUCT },
	{ "union", TOKEN_UNION },
	{ "enum", TOKEN_ENUM },
	{ "true", TOKEN_TRUE },
	{ "false", TOKEN_FALSE },
	{ ":", TOKEN_COLON },

	// separators
	{ "(", TOKEN_LPAREN },
	{ ")", TOKEN_RPAREN },
	{ "[", TOKEN_LBRACK },
	{ "]", TOKEN_RBRACK },
	{ "{", TOKEN_LBRACE },
	{ "}", TOKEN_RBRACE },
	{ ".", TOKEN_DOT },
	{ ",", TOKEN_COMMA },
	{ ";", TOKEN_SEMICOLON },

	// unary operators
	{ "++", TOKEN_INCREMENT },
	{ "--", TOKEN_DECREMENT },

	// binary operators
	{ "*",  TOKEN_ASTERISK },
	{ "/",  TOKEN_SLASH },
	{ "+",  TOKEN_PLUS },
	{ "-",  TOKEN_MINUS },
	{ "<",  TOKEN_LANGBRACK },
	{ ">",  TOKEN_RANGBRACK },
	{ "&",  TOKEN_AMPERSAND },
	{ "|",  TOKEN_PIPELINE },
	{ "^",  TOKEN_CARROT },
	{ "**", TOKEN_POW },
	{ "&&", TOKEN_AND },
	{ "||", TOKEN_OR },
	{ "==", TOKEN_EQUALS },
	{ "!=", TOKEN_NEQUALS },
	{ ">=", TOKEN_GTOET },
	{ "<=", TOKEN_LTOET },
	{ ">>", TOKEN_RSHIFT },
	{ "<<", TOKEN_LSHIFT },
	{ "->", TOKEN_SINGLE_ARROW },
	{ "=>", TOKEN_DOUBLE_ARROW },

	// assign operators
	{ "=",  TOKEN_ASSIGN },
	{ "+=", TOKEN_ADD_ASSIGN },
	{ "+=", TOKEN_ADD_ASSIGN },
	{ "-=", TOKEN_SUB_ASSIGN },
	{ "*=", TOKEN_MUL_ASSIGN },
	{ "/=", TOKEN_DIV_ASSIGN },
	{ "%=", TOKEN_MOD_ASSIGN },

	// modules
	{ "import", TOKEN_IMPORT },
	{ "export", TOKEN_EXPORT },
	{ "::", TOKEN_SCOPE }
};

const size_t token_info_count = sizeof(token_info) / sizeof(*token_info);

// data

HxTable *token_types = NULL;
CharType char_types[CHAR_TYPE_COUNT];

// functions

Error init_token_types()
{
	token_types = hxtable_create_of(TokenType);

	if (!token_types || !hxtable_reserve(token_types, token_info_count))
		return ERROR_MEMORY;

	for (size_t i = 0; i < token_info_count; ++i)
	{
		const TokenInfo *info = token_info + i;
		hxtable_set(token_types, info->key, &info->value);
	}

	return ERROR_NONE;
}

void init_char_types()
{
	// setting up identifier characters
		char_types[(size_t)'_'] = CHAR_IDENTIFIER;
		for (size_t i = 'a'; i <= 'z'; ++i)
			char_types[i] = CHAR_IDENTIFIER;
		for (size_t i = 'A'; i <= 'Z'; ++i)
			char_types[i] = CHAR_IDENTIFIER;
		for (size_t i = '0'; i <= '9'; ++i)
			char_types[i] = CHAR_DIGIT;

		// setting up separator characters
		char_types[(size_t)'('] = CHAR_SEPARATOR;
		char_types[(size_t)')'] = CHAR_SEPARATOR;
		char_types[(size_t)'['] = CHAR_SEPARATOR;
		char_types[(size_t)']'] = CHAR_SEPARATOR;
		char_types[(size_t)'{'] = CHAR_SEPARATOR;
		char_types[(size_t)'}'] = CHAR_SEPARATOR;
		char_types[(size_t)';'] = CHAR_SEPARATOR;
		char_types[(size_t)','] = CHAR_SEPARATOR;

		// dot character
		char_types[(size_t)'.'] = CHAR_DOT;

		// setting up operator characters
		char_types[(size_t)'!'] = CHAR_OPERATOR;
		char_types[(size_t)'@'] = CHAR_OPERATOR;
		char_types[(size_t)'#'] = CHAR_OPERATOR;
		char_types[(size_t)'$'] = CHAR_OPERATOR;
		char_types[(size_t)'%'] = CHAR_OPERATOR;
		char_types[(size_t)'^'] = CHAR_OPERATOR;
		char_types[(size_t)'&'] = CHAR_OPERATOR;
		char_types[(size_t)'*'] = CHAR_OPERATOR;
		char_types[(size_t)'-'] = CHAR_OPERATOR;
		char_types[(size_t)'='] = CHAR_OPERATOR;
		char_types[(size_t)'|'] = CHAR_OPERATOR;
		char_types[(size_t)'+'] = CHAR_OPERATOR;
		char_types[(size_t)'<'] = CHAR_OPERATOR;
		char_types[(size_t)'>'] = CHAR_OPERATOR;
		char_types[(size_t)'?'] = CHAR_OPERATOR;
		char_types[(size_t)'/'] = CHAR_OPERATOR;
		char_types[(size_t)':'] = CHAR_OPERATOR;

		// setting literal types
		char_types[(size_t)'\''] = CHAR_QUOTE;
		char_types[(size_t)'\"'] = CHAR_QUOTE;
}

Error tokenizer_init()
{
	try(init_token_types());
	init_char_types();

	return ERROR_NONE;
}

#define TEMP_KEY_SIZE (1023)

Error get_token_type(Token *token)
{
	assert(token != NULL);
	assert(token->string.data != NULL);
	assert(token->string.length > 0);

	if (token->string.length > TEMP_KEY_SIZE)
	{
		char *key = string_duplicate(&token->string);

		if (!key)
			return ERROR_MEMORY;

		if (!hxtable_get(token_types, &token->type, key))
			token->type = TOKEN_IDENTIFIER;

		free(key);
	}
	else
	{
		static _Thread_local char temp_key[TEMP_KEY_SIZE + 1];

		strncpy(temp_key, token->string.data, token->string.length + 1);

		if (!hxtable_get(token_types, &token->type, temp_key))
			token->type = TOKEN_IDENTIFIER;
	}

	return ERROR_NONE;
}

static inline CharType get_char_type(unsigned char c)
{
	assert(c < CHAR_TYPE_COUNT);

	return char_types[(size_t)c];
}

void tokenizer_free()
{
	hxtable_destroy(token_types);
	token_types = NULL;
}

const char *get_token_string(TokenType type)
{
	if (type == TOKEN_IDENTIFIER)
		return "<identifier>";

	for (size_t i = 0; i < token_info_count; ++i)
	{
		const TokenInfo *info = token_info + i;
		if (info->value == type)
			return info->key;
	}

	return "<unknown>";
}

static void get_next_token_pos(SourceLocation *location)
{
	while (*location->pos)
	{
		if (*location->pos > ' ')
			break;
		
		if (*location->pos == '\n')
		{
			++location->line;
			location->col = 0;
		}

		++location->col;
		++location->pos;
	}
}

static Error get_identifier_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	CharType curr_type = get_char_type(*location->pos);

	const char * const start_of_token = location->pos;

	while (curr_type == CHAR_IDENTIFIER || curr_type == CHAR_DIGIT)
	{
		++location->pos;

		curr_type = get_char_type(*location->pos);
	}

	out->line = location->line;
	out->col = location->col;
	out->string = (String)
	{
		.data = start_of_token,
		.length = location->pos - start_of_token
	};

	try(get_token_type(out));

	return ERROR_NONE;
}

static Error get_separator_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	out->string.length = 1;
	try(get_token_type(out));

	return ERROR_NONE;
}

static Error get_dot_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	// if (char_types[*pos] == CHAR_DIGIT)
	// {
	// 	out.type = TOKEN_FLOAT_LITERAL;
	// 	goto float_literal;
	// }
	// while (char_types[*pos] == CHAR_DOT) ++pos;
	// out.str.len = pos - out.str.ptr;
	// out.type = TOKEN_DOT + out.str.len - 1;
	// if (out.str.len > 3) out.type = TOKEN_ERROR;
	// goto finish;

	return not_implemented_error();
}

static Error get_digit_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	// while (*pos)
	// {
	// 	// if encounters a dot
	// 	if (pos[0] == '.')
	// 	{	
	// 		// range or elipsis
	// 		if (pos[1] == '.') break;

	// 		// if multiple dots, flag float or error
	// 		if (!out.type) out.type = TOKEN_FLOAT_LITERAL;
	// 		else out.type = TOKEN_ERROR;

	// 		pos += 1;
	// 		continue;
	// 	}
	// 	// if encountering non digit/dot
	// 	if (char_types[*pos] != CHAR_DIGIT) break;
	// 	pos += 1;
	// }
	// out.str.len = pos - out.str.ptr;
	// if (!out.type) out.type = TOKEN_INT_LITERAL;

	// goto finish;

	return not_implemented_error();
}

static Error get_operator_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	// while (char_types[*pos] == CHAR_OPERATOR) ++pos;
	// out.str.len = pos - out.str.ptr;
	// if (out.str.len == 1)
	// {
	// 	out.type = char_token_types[*out.str.ptr];
	// 	goto finish;
	// }
	// goto table_lookup;

	return not_implemented_error();
}

static Error get_quote_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	// // got till non-escaped end of string
	// while (pos[0] != out.str.ptr[0] && pos[-1] != '\\') ++pos;
	// ++out.str.ptr;
	// out.str.len = pos - out.str.ptr;
	// ++pos;
	// if (out.str.ptr[-1] == '\'')
	// {
	// 	out.type = TOKEN_CHAR_LITERAL;
	// }
	// else if (out.str.ptr[-1] == '\"')
	// {
	// 	out.type = TOKEN_STR_LITERAL;
	// }
	// goto finish;

	return not_implemented_error();
}

static Error get_next_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	get_next_token_pos(location);

	out->string.data = location->pos;
	out->line = location->line;
	out->col = location->col;

	size_t character = *location->pos;

	if (!character)
	{
		*out = token_default();
		return ERROR_NONE;
	}
	
	CharType type = char_types[character];

	switch (type)
	{
		case CHAR_IDENTIFIER:
			return get_identifier_token(out, location);
		case CHAR_SEPARATOR:
			return get_separator_token(out, location);
		case CHAR_DOT:
			return get_dot_token(out, location);
		case CHAR_DIGIT:
			return get_digit_token(out, location);
		case CHAR_OPERATOR:
			return get_operator_token(out, location);
		case CHAR_QUOTE:
			return get_quote_token(out, location);
		default:
			break;
	}

	return ERROR_ARGUMENT;
}

static inline Error assure_tokens_size(HxArray *tokens)
{
	size_t current_length = hxarray_length(tokens);
			
	if (current_length == hxarray_capacity(tokens))
	{
		if (!hxarray_reserve(tokens, current_length * 2))
			return ERROR_MEMORY;
	}

	return ERROR_NONE;
}

static inline Error push_next_token(HxArray *tokens, SourceLocation *location)
{
	Token token;

	try(get_next_token(&token, location));
	if (!hxarray_push(tokens, &token))
		return ERROR_MEMORY;
	
	return ERROR_NONE;
}

Error tokenize(HxArray **out, const char *src)
{
	HxArray *tokens = hxarray_create_of(Token);

	if (!tokens)
		return ERROR_MEMORY;

	SourceLocation location = source_location_create(src);

	while (true)
	{
		Error error = assure_tokens_size(tokens);
		if (error)
		{
			hxarray_destroy(tokens);
			return error;
		}
		
		error = push_next_token(tokens, &location);
		if (error)
		{
			hxarray_destroy(tokens);
			return error;
		}

		Token *back = hxarray_back(tokens);

		printf("Parsed token: %s\n", get_token_string(back->type));

		if (back->type == TOKEN_END_OF_FILE)
			break;
	}

	*out = tokens;

	return ERROR_NONE;
}
