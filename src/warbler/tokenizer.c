#include <warbler/tokenizer.h>

// local includes
#include <warbler/error.h>

// standard libary
#include <string.h>

// external library
#define HIRZEL_IMPLEMENT
#include <hirzel/util/table.h>

#define CHAR_TYPE_COUNT (128)

typedef enum CharType
{
	CHAR_INVALID,
	CHAR_IDENTIFIER,
	CHAR_SEPARATOR,
	CHAR_DOT,
	CHAR_DIGIT,
	CHAR_OPERATOR,
	CHAR_QUOTE
}
CharType;

typedef struct TokenInfo
{
	const char *str;
	TokenType type;
}
TokenInfo;

HxTable *token_types = NULL;
TokenType char_token_types[CHAR_TYPE_COUNT];
CharType char_types[CHAR_TYPE_COUNT];

const TokenInfo token_info[] =
{
	// misc keywords
	{ "func", TOK_FUNC },
	{ "var", TOK_VAR },
	{ "type", TOK_TYPE },
	{ "return", TOK_RETURN },
	{ "for", TOK_FOR },
	{ "while", TOK_WHILE },
	{ "loop", TOK_LOOP },
	{ "continue", TOK_CONTINUE },
	{ "break", TOK_BREAK },
	{ "if", TOK_IF },
	{ "else", TOK_ELSE },
	{ "switch", TOK_SWITCH },
	{ "case", TOK_CASE },

	// typenames
	{ "struct", TOK_STRUCT },
	{ "union", TOK_UNION },
	{ "enum", TOK_ENUM },
	{ "true", TOK_TRUE },
	{ "false", TOK_FALSE },
	{ ":", TOK_COLON },

	// separators
	{ "(", TOK_LPAREN },
	{ ")", TOK_RPAREN },
	{ "[", TOK_LBRACK },
	{ "]", TOK_RBRACK },
	{ "{", TOK_LBRACE },
	{ "}", TOK_RBRACE },
	{ ".", TOK_DOT },
	{ ",", TOK_COMMA },
	{ ";", TOK_SEMICOLON },

	// unary operators
	{ "++", TOK_INCREMENT },
	{ "--", TOK_DECREMENT },

	// binary operators
	{ "*",  TOK_ASTERISK },
	{ "/",  TOK_SLASH },
	{ "+",  TOK_PLUS },
	{ "-",  TOK_MINUS },
	{ "<",  TOK_LANGBRACK },
	{ ">",  TOK_RANGBRACK },
	{ "&",  TOK_AMPERSAND },
	{ "|",  TOK_PIPELINE },
	{ "^",  TOK_CARROT },
	{ "**", TOK_POW },
	{ "&&", TOK_AND },
	{ "||", TOK_OR },
	{ "==", TOK_EQUALS },
	{ "!=", TOK_NEQUALS },
	{ ">=", TOK_GTOET },
	{ "<=", TOK_LTOET },
	{ ">>", TOK_RSHIFT },
	{ "<<", TOK_LSHIFT },
	{ "->", TOK_SINGLE_ARROW },
	{ "=>", TOK_DOUBLE_ARROW },

	// assign operators
	{ "=",  TOK_ASSIGN },
	{ "+=", TOK_ADD_ASSIGN },
	{ "+=", TOK_ADD_ASSIGN },
	{ "-=", TOK_SUB_ASSIGN },
	{ "*=", TOK_MUL_ASSIGN },
	{ "/=", TOK_DIV_ASSIGN },
	{ "%=", TOK_MOD_ASSIGN },

	// modules
	{ "import", TOK_IMPORT },
	{ "export", TOK_EXPORT },
	{ "::", TOK_SCOPE }
};

const size_t token_info_count = sizeof(token_info) / sizeof(*token_info);

static HxTable *initialize_token_types()
{
	HxTable *out = createHxTableOf(TokenType);

	if (!out)
	{
		print_error("failed to initialize token type table");

		return NULL;
	}

	if (reserveHxTable(out, token_info_count))
	{
		destroyHxTable(out);
		print_error("failed to allocate token type table");

		return NULL;
	}

	for (size_t i = 0; i < token_info_count; ++i)
	{
		const TokenInfo *info = token_info + i;

		if (!setHxTable(token_types, info->str, &info->type))
		{
			destroyHxTable(out);
			print_error("failed to assign token type table");

			return NULL;
		}
	}

	return out;
}

void initialize_char_types(CharType *types)
{
	// setting up identifier characters
	types['_'] = CHAR_IDENTIFIER;
	for (size_t i = 'a'; i <= 'z'; ++i)
		types[i] = CHAR_IDENTIFIER;
	for (size_t i = 'A'; i <= 'Z'; ++i)
		types[i] = CHAR_IDENTIFIER;
	for (size_t i = '0'; i <= '9'; ++i)
		types[i] = CHAR_DIGIT;

	// setting up separator characters
	types['('] = CHAR_SEPARATOR;
	types[')'] = CHAR_SEPARATOR;
	types['['] = CHAR_SEPARATOR;
	types[']'] = CHAR_SEPARATOR;
	types['{'] = CHAR_SEPARATOR;
	types['}'] = CHAR_SEPARATOR;
	types[';'] = CHAR_SEPARATOR;
	types[','] = CHAR_SEPARATOR;

	// dot character
	types['.'] = CHAR_DOT;

	// setting up operator characters
	types['!'] = CHAR_OPERATOR;
	types['@'] = CHAR_OPERATOR;
	types['#'] = CHAR_OPERATOR;
	types['$'] = CHAR_OPERATOR;
	types['%'] = CHAR_OPERATOR;
	types['^'] = CHAR_OPERATOR;
	types['&'] = CHAR_OPERATOR;
	types['*'] = CHAR_OPERATOR;
	types['-'] = CHAR_OPERATOR;
	types['='] = CHAR_OPERATOR;
	types['|'] = CHAR_OPERATOR;
	types['+'] = CHAR_OPERATOR;
	types['<'] = CHAR_OPERATOR;
	types['>'] = CHAR_OPERATOR;
	types['?'] = CHAR_OPERATOR;
	types['/'] = CHAR_OPERATOR;
	types[':'] = CHAR_OPERATOR;

	// setting literal types
	types['\''] = CHAR_QUOTE;
	types['\"'] = CHAR_QUOTE;
}

bool initialize()
{
	if (token_types != NULL)
	{
		print_error("unnecessary double initialization of tokenizer");

		return false;
	}

	

	token_types = initialize_token_types();

	if (!token_types)
		return false;

	return true;	
}


token_t lex_next_token(char **src, unsigned line, unsigned short col)
{
	token_t out = {0};
	char *pos = *src;

	// skip to next visible character
	while (*pos < 33)
	{
		if (*pos == '\n')
		{
			line += 1;
			col = 0;
		}
		if (*pos == 0)
		{
			out.line = line;
			out.col = col;
			out.str.ptr = NULL;
			out.str.len = 0;
			return out;
		}
		col += 1;
		++pos;
	}

	// storing position in token
	out.line = line;
	out.col = col;
	out.str.ptr = pos;
	char type = char_types[*pos];
	pos += 1;

	switch (type)
	{
		case CHAR_IDENTIFIER:;
			char curr_type = char_types[*pos];
			while (curr_type == CHAR_IDENTIFIER || curr_type == CHAR_DIGIT)
			{
				++pos;
				curr_type = char_types[*pos];
			}
			out.str.len = pos - out.str.ptr;

			// slight optimization as most keywords and operators are short
			if (out.str.len > MAX_KEYWORD_LENGTH)
			{
				out.type = TOK_IDENTIFIER;
				goto finish;
			}

			// else table lookup
			goto table_lookup;
			
		case CHAR_SEPARATOR:
			out.type = char_token_types[*out.str.ptr];
			out.str.len = 1;
			goto finish;

		case CHAR_DOT:
			if (char_types[*pos] == CHAR_DIGIT)
			{
				out.type = TOK_FLOAT_LITERAL;
				goto float_literal;
			}
			while (char_types[*pos] == CHAR_DOT) ++pos;
			out.str.len = pos - out.str.ptr;
			out.type = TOK_DOT + out.str.len - 1;
			if (out.str.len > 3) out.type = TOK_ERROR;
			goto finish;

		case CHAR_OPERATOR:

			while (char_types[*pos] == CHAR_OPERATOR) ++pos;
			out.str.len = pos - out.str.ptr;
			if (out.str.len == 1)
			{
				out.type = char_token_types[*out.str.ptr];
				goto finish;
			}
			goto table_lookup;


		float_literal:
		case CHAR_DIGIT:
			while (*pos)
			{
				// if encounters a dot
				if (pos[0] == '.')
				{	
					// range or elipsis
					if (pos[1] == '.') break;

					// if multiple dots, flag float or error
					if (!out.type) out.type = TOK_FLOAT_LITERAL;
					else out.type = TOK_ERROR;

					pos += 1;
					continue;
				}
				// if encountering non digit/dot
				if (char_types[*pos] != CHAR_DIGIT) break;
				pos += 1;
			}
			out.str.len = pos - out.str.ptr;
			if (!out.type) out.type = TOK_INT_LITERAL;

			goto finish;

		case CHAR_QUOTE:
			// got till non-escaped end of string
			while (pos[0] != out.str.ptr[0] && pos[-1] != '\\') ++pos;
			out.str.ptr += 1;
			out.str.len = pos - out.str.ptr;
			pos += 1;
			if (out.str.ptr[-1] == '\'')
			{
				out.type = TOK_CHAR_LITERAL;
			}
			else if (out.str.ptr[-1] == '\"')
			{
				out.type = TOK_STR_LITERAL;
			}
			goto finish;

		default:
			out.str.len = 1;
			out.type = TOK_ERROR;
			goto finish;
	}

	
finish:
	*src = pos;
	return out;

table_lookup:;
	char tmp[MAX_KEYWORD_LENGTH + 1];

	// table lookup
	for (int i = 0; i < out.str.len; ++i)
	{
		tmp[i] = out.str.ptr[i];
	}

	tmp[out.str.len] = 0;
	out.type = chartbl_get(token_types, tmp);

	// if it failed to find matching key
	if (out.type == 0)
	{
		if (type == CHAR_IDENTIFIER)
		{
			out.type = TOK_IDENTIFIER;
		}
		else
		{
			out.type = TOK_ERROR;
		}
	}

	goto finish;
}

std::vector<Token> lex(char *src)
{
	auto out = std::vector<Token>();

	token_t tok = get_next_token((&src, 1, 1);
	while (1)
	{
		if (tok.type == TOK_ERROR)
		{
			lex_error(&tok);
			return NULL;
		}

		toklist_push(out, tok);

		// adding on the eof for memory safety when peeking
		if (tok.type == TOK_EOF) break;

		tok = lex_next_token(&src, tok.line, tok.col + tok.str.len);
	}

	return out;
}
