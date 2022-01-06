#include <warbler/tokenizer.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <string.h>
#include <stdlib.h>

// external headers
#include <hirzel/table.h>

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
	{ "not", TOKEN_NOT }
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
	{
		error("failed to reserve memory for token table");
		return ERROR_MEMORY;
	}

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

static Error get_token_type(Token *token)
{
	assert(token->text.data != NULL);
	assert(token->text.length > 0);

	if (token->text.length > TEMP_KEY_SIZE)
	{
		char *key = string_duplicate(&token->text);

		if (!key)
			return ERROR_MEMORY;

		if (!hxtable_get(token_types, &token->type, key))
			token->type = TOKEN_IDENTIFIER;

		free(key);
	}
	else
	{
		static char temp_key[TEMP_KEY_SIZE + 1];

		strncpy(temp_key, token->text.data, token->text.length);
		temp_key[token->text.length] = '\0';

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

static Token find_next_token(const Token *last_token)
{
	Token out = (Token)
	{
		.filename = last_token->filename,
		.line = last_token->line,
		.col = last_token->col,
		.text = (String)
		{
			.data = last_token->text.data + last_token->text.length,
			.length = 0
		},
		.type = TOKEN_END_OF_FILE
	};

	register const char * pos = out.text.data;

	while (true)
	{
		if (*pos == '\0')
			break;

		if (*pos > ' ')
			break;
		
		if (*pos == '\n')
		{
			++out.line;
			out.col = 0;
		}

		++out.col;
		++pos;
	}

	out.text.data = pos;

	return out;
}

static inline bool is_char_alphanumeric(char c)
{
	CharType type = get_char_type(c);

	return type == CHAR_IDENTIFIER || type == CHAR_DIGIT;
}

static Error get_identifier_token(Token *self)
{
	Error error;

	const char *pos = self->text.data + 1;

	while (is_char_alphanumeric(*pos))
		++pos;

	self->text.length = pos - self->text.data;

	if ((error = get_token_type(self)))
		return error;

	return ERROR_NONE;
}

static Error get_separator_token(Token *self)
{
	self->text.length = 1;

	switch (self->text.data[0])
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
			errorf("invalid character given for seprarator token: '%c'\n", self->text.data[0]);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

static Error get_digit_token(Token *self)
{
	assert(self != NULL);

	const char *pos = self->text.data;
	bool is_float = false;

	while (true)
	{
		CharType type = get_char_type(*pos);

		switch (type)
		{
			case CHAR_DOT:
				if (is_float)
				{
					errort("extra decimal in float literal", self);
					return ERROR_ARGUMENT;
				}

				is_float = true;
				++pos;
				continue;

			case CHAR_DIGIT:
				++pos;
				continue;

			default:
				break;
		}

		break;
	}


	self->text.length = pos - self->text.data;
	self->type = is_float
		? TOKEN_FLOAT_LITERAL
		: TOKEN_INTEGER_LITERAL;

	return ERROR_NONE;
}

static Error get_dot_token(Token *self)
{
	assert(self != NULL);

	const char *pos = self->text.data;

	if (get_char_type(pos[1]) == CHAR_DIGIT)
		return get_digit_token(self);

	++pos;

	while (get_char_type(*pos) == CHAR_DOT)
		++pos;

	self->text.length = pos - self->text.data;

	switch (self->text.length)
	{
		case 1:
			self->type = TOKEN_DOT;
			break;

		case 3:
			self->type = TOKEN_ELIPSIS;
			break;

		default:
			errort("invalid dot token", self);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

static inline void get_plus_operator(Token *self)
{
	switch (self->text.data[1])
	{
		case '+':
			self->type = TOKEN_INCREMENT;
			self->text.length = 2;
			break;

		case '=':
			self->type = TOKEN_ADD_ASSIGN;
			self->text.length = 2;
			break;

		default:
			self->type = TOKEN_PLUS;
			self->text.length = 1;
			break;
	}
}

static inline void get_hyphen_operator(Token *self)
{
	switch (self->text.data[1])
	{
		case '-': // --
			self->type = TOKEN_DECREMENT;
			self->text.length = 2;
			break;

		case '=': // -=
			self->type = TOKEN_SUBTRACT_ASSIGN;
			self->text.length = 2;
			break;

		case '>': // ->
			self->type = TOKEN_SINGLE_ARROW;
			self->text.length = 2;
			break;

		default: // -
			self->type = TOKEN_MINUS;
			self->text.length = 1;
			break;
	}
}

static inline void get_asterisk_operator(Token *self)
{
	switch (self->text.data[1])
	{
		case '*': // **
			self->type = TOKEN_POW;
			self->text.length = 2;
			break;

		case '=': // *=
			self->type = TOKEN_MULTIPLY_ASSIGN;
			self->text.length = 2;
			break;

		default: // *
			self->type = TOKEN_ASTERISK;
			self->text.length = 1;
			break;
	}
}

static inline void get_slash_operator(Token *self)
{
	if (self->text.data[1] == '=')
	{
		self->type = TOKEN_DIVIDE_ASSIGN;
		self->text.length = 2;
	}
	else
	{
		self->type = TOKEN_SLASH;
		self->text.length = 1;
	}
}

static inline void get_langbrack_operator(Token *self)
{
	switch (self->text.data[1])
	{
		case '<': // <<
			if (self->text.data[2] == '=') // <<=
			{
				self->type = TOKEN_LSHIFT_ASSIGN;
				self->text.length = 3;
			}
			else
			{
				self->type = TOKEN_LSHIFT;
				self->text.length = 2;
			}
			break;

		case '=': // <=
			self->type = TOKEN_LESS_EQUALS;
			self->text.length = 2;
			break;

		default: // <
			self->type = TOKEN_LANGBRACK;
			self->text.length = 1;
			break;
	}
}

static inline void get_rangbrack_operator(Token *self)
{
	switch (self->text.data[1])
	{
		case '>': // >>
			if (self->text.data[2] == '=') // >>=
			{
				self->type = TOKEN_RSHIFT_ASSIGN;
				self->text.length = 3;
			}
			else
			{
				self->type = TOKEN_RSHIFT;
				self->text.length = 2;
			}
			break;

		case '=': // <=
			self->type = TOKEN_GREATER_EQUALS;
			self->text.length = 2;
			break;

		default: // >
			self->type = TOKEN_RANGBRACK;
			self->text.length = 1;
			break;
	}
}

static inline void get_ampersand_operator(Token *self)
{
	if (self->text.data[1] == '=')
	{
		self->type = TOKEN_BITAND_ASSIGN;
		self->text.length = 2;
	}
	else
	{
		self->type = TOKEN_AMPERSAND;
		self->text.length = 1;
	}
}

static inline void get_pipeline_operator(Token *self)
{
	if (self->text.data[1] == '=')
	{
		self->type = TOKEN_BITOR_ASSIGN;
		self->text.length = 2;
	}
	else
	{
		self->type = TOKEN_PIPELINE;
		self->text.length = 1;
	}
}

static inline void get_carrot_operator(Token *self)
{
	if (self->text.data[1] == '=')
	{
		self->type = TOKEN_BITXOR_ASSIGN;
		self->text.length = 2;
	}
	else
	{
		self->type = TOKEN_CARROT;
		self->text.length = 1;
	}
}

static inline void get_equals_operator(Token *self)
{
	switch (self->text.data[1])
	{
		case '=':
			self->type = TOKEN_EQUALS;
			self->text.length = 2;
			break;

		case '>':
			self->type = TOKEN_DOUBLE_ARROW;
			self->text.length = 2;
			break;

		default:
			self->type = TOKEN_ASSIGN;
			self->text.length = 1;
			break;
	}
}

static inline void get_exclamation_operator(Token *self)
{
	if (self->text.data[1] == '=')
	{
		self->type = TOKEN_NOT_EQUALS;
		self->text.length = 2;
	}
	else
	{
		self->type = TOKEN_EXCLAMATION;
		self->text.length = 1;
	}
}

static inline void get_question_operator(Token *self)
{
	if (self->text.data[1] == '?')
	{
		self->type = TOKEN_OPTION;
		self->text.length = 2;
	}
	else
	{
		self->type = TOKEN_QUESTION;
		self->text.length = 1;
	}
}

static inline void get_modulus_operator(Token *self)
{
	if (self->text.data[1] == '=')
	{
		self->type = TOKEN_MODULUS_ASSIGN;
		self->text.length = 2;
	}
	else
	{
		self->type = TOKEN_MODULUS;
		self->text.length = 1;
	}
}

static inline void get_colon_operator(Token *self)
{
	if (self->text.data[1] == ':')
	{
		self->type = TOKEN_SCOPE;
		self->text.length = 2;
	}
	else
	{
		self->type = TOKEN_COLON;
		self->text.length = 1;
	}
}

static Error get_operator_token(Token *self)
{
	char character = self->text.data[0];

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

		case '%': // %, %=
			get_modulus_operator(self);
			break;

		case ':': // :, ::
			get_colon_operator(self);
			break;

		default:
			errorf("invalid operator token character: %c", character);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

static inline bool is_end_of_text_literal(const char *pos, char terminal_char)
{
	return pos[0] == terminal_char && pos[-1] != '\\';
}

static Error get_quote_token(Token *self)
{	
	char terminal_char = self->text.data[0];

	const char *pos = self->text.data + 1;
	while (*pos && !is_end_of_text_literal(pos, terminal_char))
		++pos;

	if (*pos == '\0')
	{
		error("unterminated string literal");
		return ERROR_ARGUMENT;
	}

	++pos;

	self->text.length = pos - self->text.data;

	if (self->text.data[0] == '\'')
	{
		self->type = TOKEN_CHAR_LITERAL;
	}
	else if (self->text.data[0] == '\"')
	{
		self->type = TOKEN_STRING_LITERAL;
	}
		
	return ERROR_NONE;
}

static Error get_next_token(Token *self)
{
	assert(self != NULL);

	CharType type = get_char_type(self->text.data[0]);

	switch (type)
	{
		case CHAR_NULL:
			*self = token_default();
			return ERROR_NONE;

		case CHAR_IDENTIFIER:
			return get_identifier_token(self);

		case CHAR_SEPARATOR:
			return get_separator_token(self);

		case CHAR_DOT:
			return get_dot_token(self);

		case CHAR_DIGIT:
			return get_digit_token(self);

		case CHAR_OPERATOR:
			return get_operator_token(self);

		case CHAR_QUOTE:
			return get_quote_token(self);

		default:
			break;
	}

	printf("text: %p\n", self->text.data);
	printf("value: %d\n", self->text.data[0]);

	errorf("invalid character in source file: %c\n", self->text.data[0]);
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

Error tokenize(TokenArray *out, const char *filename, const char *src)
{
	HxArray *tokens = hxarray_create_of(Token);

	if (!tokens)
		return ERROR_MEMORY;

	if (!hxarray_reserve(tokens, 1))
	{
		error("failed to allocate memory for initial token");
		return ERROR_MEMORY;
	}

	Token initial = token_initial(filename, src);
	Token *previous = &initial;

	do
	{
		Token token = find_next_token(previous);
		try(get_next_token(&token));		
		try(assure_tokens_size(tokens));
		if (!hxarray_push(tokens, &token))
			return ERROR_MEMORY;

		previous = hxarray_back(tokens);
	}
	while (previous->type != TOKEN_END_OF_FILE);

	*out = (TokenArray)
	{
		.length = hxarray_length(tokens),
		.data = hxarray_front(tokens)
	};

	free(tokens);

	return ERROR_NONE;
}
