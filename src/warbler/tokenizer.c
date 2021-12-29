#include <warbler/tokenizer.h>

// local headers
#include <warbler/error.h>

// standard headers
#include <string.h>
#include <stdlib.h>

// external headers
#include <hirzel/table.h>
#include <hirzel/array.h>

typedef enum CharType
{
	CHAR_INVALID,
	CHAR_NULL,
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

const TokenInfo keywords[] =
{
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
	{ "struct", TOKEN_STRUCT },
	{ "union", TOKEN_UNION },
	{ "enum", TOKEN_ENUM },
	{ "true", TOKEN_TRUE },
	{ "false", TOKEN_FALSE },
	{ "import", TOKEN_IMPORT },
	{ "export", TOKEN_EXPORT },
	{ "and", TOKEN_AND },
	{ "or", TOKEN_OR },
	{ "xor", TOKEN_XOR },
	{ "not", TOKEN_NOT },

	{ "++", TOKEN_INCREMENT },
	{ "--", TOKEN_DECREMENT },
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
	{ "==", TOKEN_EQUALS },
	{ "!=", TOKEN_NEQUALS },
	{ ">=", TOKEN_GREATER_EQUALS },
	{ "<=", TOKEN_LESS_EQUALS },
	{ ">>", TOKEN_RSHIFT },
	{ "<<", TOKEN_LSHIFT },
	{ "->", TOKEN_SINGLE_ARROW },
	{ "=>", TOKEN_DOUBLE_ARROW },
	{ "=",  TOKEN_ASSIGN },
	{ "+=", TOKEN_ADD_ASSIGN },
	{ "-=", TOKEN_SUBTRACT_ASSIGN },
	{ "*=", TOKEN_MULTIPLY_ASSIGN },
	{ "/=", TOKEN_DIVIDE_ASSIGN },
	{ "%=", TOKEN_MODULUS_ASSIGN },
	{ ":=", TOKEN_BECOME_ASSIGN },
	{ ":", TOKEN_COLON },
	{ "::", TOKEN_SCOPE }
};

const size_t keyword_count = sizeof(keywords) / sizeof(*keywords);

// data

HxTable *token_types = NULL;
CharType char_types[CHAR_TYPE_COUNT];

// functions

Error init_token_types()
{
	token_types = hxtable_create_of(TokenType);

	if (!token_types || !hxtable_reserve(token_types, keyword_count))
		return ERROR_MEMORY;

	for (size_t i = 0; i < keyword_count; ++i)
	{
		const TokenInfo *info = keywords + i;
		hxtable_set(token_types, info->key, &info->value);
	}

	return ERROR_NONE;
}

void init_char_types()
{
	char_types[0] = CHAR_NULL;

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
	Error error;

	if ((error = init_token_types()))
		return error;

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
	else if (type == TOKEN_END_OF_FILE)
		return "<end of file>";

	for (size_t i = 0; i < keyword_count; ++i)
	{
		const TokenInfo *info = keywords + i;
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

static inline bool is_char_alphanumeric(char c)
{
	CharType type = get_char_type(c);

	return type == CHAR_IDENTIFIER || type == CHAR_DIGIT;
}

static Error get_identifier_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	Error error;

	while (is_char_alphanumeric(*location->pos))
		++location->pos;

	out->string.length = location->pos - out->string.data;

	if ((error = get_token_type(out)))
		return error;

	return ERROR_NONE;
}

static Error get_separator_token(Token *self, SourceLocation *location)
{
	assert(self != NULL);
	assert(location != NULL);

	self->string.length = 1;

	switch (self->string.data[0])
	{
		case '(':
			self->type = TOKEN_LPAREN;
			break;

		case ')':
			self->type = TOKEN_RPAREN;
			break;

		case '[':
			self->type = TOKEN_LBRACK;
			break;

		case ']':
			self->type = TOKEN_RBRACK;
			break;

		case '{':
			self->type = TOKEN_LBRACE;
			break;

		case '}':
			self->type = TOKEN_RBRACE;
			break;

		case ',':
			self->type = TOKEN_COMMA;
			break;

		case ';':
			self->type = TOKEN_SEMICOLON;
			break;
		
		default:
			print_errorf("invalid character given for seprarator token: '%c'\n", self->string.data[0]);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

static Error get_digit_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	bool is_float = false;

	while (true)
	{
		CharType type = get_char_type(*location->pos);

		switch (type)
		{
			case CHAR_DOT:
				if (is_float)
					return ERROR_ARGUMENT;

				is_float = true;
				++location->pos;
				continue;

			case CHAR_DIGIT:
				++location->pos;
				continue;

			default:
				break;
		}

		break;
	}

	out->string.length = location->pos - out->string.data;
	out->type = is_float
		? TOKEN_FLOAT_LITERAL
		: TOKEN_INTEGER_LITERAL;

	return ERROR_NONE;
}

static Error get_dot_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	if (get_char_type(location->pos[1]) == CHAR_DIGIT)
	{
		--location->pos;

		return get_digit_token(out, location);
	}

	while (get_char_type(*location->pos) == CHAR_DOT)
		++location->pos;

	out->string.length = location->pos - out->string.data;

	switch (out->string.length)
	{
		case 1:
			out->type = TOKEN_DOT;
			break;

		case 3:
			out->type = TOKEN_ELIPSIS;
			break;

		default:
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

static inline void get_plus_operator(Token *self)
{
	switch (self->string.data[1])
	{
		case '+':
			self->type = TOKEN_INCREMENT;
			self->string.length = 2;
			break;

		case '=':
			self->type = TOKEN_ADD_ASSIGN;
			self->string.length = 2;
			break;

		default:
			self->type = TOKEN_PLUS;
			self->string.length = 1;
			break;
	}
}

static inline Error get_hyphen_operator(Token *self)
{
	switch (self->string.data[1])
	{
		case '-':
			self->type = TOKEN_DECREMENT;
			self->string.length = 2;
			break;

		case '=':
			self->type = TOKEN_SUBTRACT_ASSIGN;
			self->string.length = 2;
			break;

		case '>':
			self->type = TOKEN_SINGLE_ARROW;
			self->string.length = 2;
			break;

		default:
			self->type = TOKEN_MINUS;
			self->string.length = 1;
			break;
	}
}

static Error get_operator_token(Token *self, SourceLocation *location)
{
	assert(self != NULL);
	assert(location != NULL);

	char character = self->string.data[0];

	switch (character)
	{
		case '+': // +, ++, +=
			get_plus_operator(self);
			break;

		case '-': // -, --, -=, ->
			get_hyphen_operator(self);
			break;

		case '*': // *, **, *=
			get_asterisk_operator(self);
			break;

		case '/': // /, /=
			get_slash_operator(self);
			break;

		case '<': // <, <<, <=
			get_langbrack_operator(self);
			break;

		case '>': // >, >>, >=
			get_rangbrack_operator(self);
			break;

		case '&': // &, &=
			get_ampersand_operator(self);
			break;

		case '|': // |, |=
			get_pipeline_operator(self);
			break;

		case '^': // ^, ^=
			get_carrot_operator(self);
			break;

		case '=': // =, ==, =>
			get_equals_operator(self);
			break;

		case '!': // !, !=
			get_exclamation_operator(self);
			break;

		case '?': // ?, ??
			get_question_operator(self);
			break;

		case '%=': // %, %=
			get_modulus_operator(self);
			break;

		case ':': // :, ::, :=
			get_colon_operator(self);
			break;

		default:
			print_errorf("invalid operator token character: %c", character);
			return ERROR_ARGUMENT;
	}

	location->pos += self->string.length;

	return ERROR_NONE;
}

static inline bool is_end_of_text_literal(SourceLocation *location, char terminal_char)
{
	return location->pos[0] == terminal_char && location->pos[-1] != '\\';
}

static Error get_quote_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);
	
	char terminal_char = out->string.data[0];

	while (*location->pos && !is_end_of_text_literal(location, terminal_char))
		++location->pos;

	++location->pos;

	out->string.length = location->pos - out->string.data;

	if (out->string.data[0] == '\'')
	{
		out->type = TOKEN_CHAR_LITERAL;
	}
	else if (out->string.data[0] == '\"')
	{
		out->type = TOKEN_STRING_LITERAL;
	}
		
	return ERROR_NONE;
}

static Error get_next_token(Token *out, SourceLocation *location)
{
	assert(out != NULL);
	assert(location != NULL);

	get_next_token_pos(location);

	out->string.data = location->pos;
	out->line = location->line;
	out->col = location->col;

	CharType type = get_char_type(*location->pos);

	++location->pos;

	switch (type)
	{
		case CHAR_NULL:
			*out = token_default();
			return ERROR_NONE;

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
	Error error;

	if ((error = get_next_token(&token, location)))
		return error;

	if (!hxarray_push(tokens, &token))
		return ERROR_MEMORY;
	
	return ERROR_NONE;
}

static inline bool is_dynamic_token(TokenType type)
{
	switch (type)
	{
		case TOKEN_INTEGER_LITERAL:
		case TOKEN_FLOAT_LITERAL:
		case TOKEN_STRING_LITERAL:
		case TOKEN_CHAR_LITERAL:
			return true;

		default:
			return false;
	}
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

		if (back->type == TOKEN_END_OF_FILE)
			break;
	}

	*out = tokens;

	return ERROR_NONE;
}
