// main header
#include <grackle/lex.h>

// local includes
#include <grackle/chartbl.h>

// standard libary
#include <stdlib.h>


char char_types[128];
char ctok_types[128];
chartbl_t *tok_types = NULL;

void lex_init()
{
	// setting up identifier characters
	char_types['_'] = CHAR_IDENTIFIER;
	for (int i = 'a'; i <= 'z'; ++i) char_types[i] = CHAR_IDENTIFIER;
	for (int i = 'A'; i <= 'Z'; ++i) char_types[i] = CHAR_IDENTIFIER;

	// setting up digit characters
	for (int i = '0'; i <= '9'; ++i) char_types[i] = CHAR_DIGIT;

	// setting up separator characters
	char_types['('] = CHAR_SEPARATOR;
	char_types[')'] = CHAR_SEPARATOR;
	char_types['['] = CHAR_SEPARATOR;
	char_types[']'] = CHAR_SEPARATOR;
	char_types['{'] = CHAR_SEPARATOR;
	char_types['}'] = CHAR_SEPARATOR;
	char_types[';'] = CHAR_SEPARATOR;
	char_types[','] = CHAR_SEPARATOR;
	char_types['.'] = CHAR_SEPARATOR;

	// setting up operator characters
	char_types['!'] = CHAR_OPERATOR;
	char_types['$'] = CHAR_OPERATOR;
	char_types['%'] = CHAR_OPERATOR;
	char_types['?'] = CHAR_OPERATOR;
	char_types['^'] = CHAR_OPERATOR;
	char_types['&'] = CHAR_OPERATOR;
	char_types['*'] = CHAR_OPERATOR;
	char_types['/'] = CHAR_OPERATOR;
	char_types['+'] = CHAR_OPERATOR;
	char_types['-'] = CHAR_OPERATOR;
	char_types['='] = CHAR_OPERATOR;
	char_types['<'] = CHAR_OPERATOR;
	char_types['>'] = CHAR_OPERATOR;

	// setting literal types
	char_types['\''] = CHAR_QUOTE;
	char_types['\"'] = CHAR_QUOTE;

	// making the rest of visible characters invalid
	for (unsigned i = 33; i < sizeof(char_types); ++i)
	{
		if (char_types[i] == CHAR_NO_TYPE) char_types[i] = CHAR_INVALID;
	}

	// Assignment
	ctok_types['='] = TOK_ASSIGN;

	// Separators
	ctok_types['('] = TOK_LPAREN;
	ctok_types[')'] = TOK_RPAREN;
	ctok_types['['] = TOK_LBRACK;
	ctok_types[']'] = TOK_RBRACK;
	ctok_types['{'] = TOK_LBRACE;
	ctok_types['}'] = TOK_RBRACE;
	ctok_types[';'] = TOK_SEMICOLON;
	ctok_types['*'] = TOK_ASTERISK;

	// initializing token types
	tok_types = chartbl_create();
	chartbl_set(tok_types, "return", TOK_RETURN);
	chartbl_set(tok_types, "+=", TOK_ADD_ASSIGN);
}

void lex_cleanup()
{
	chartbl_destroy(tok_types);
}

token_t lex_next_token(char **src)
{
	token_t out;
	out.type = TOK_NO_TYPE;
	char *pos = *src;

	// skip to next visible character
	while (*pos < 33)
	{
		if (*pos == 0) return out;
		++pos;
	}

	// storing position in token
	out.str.ptr = pos;

	char type = char_types[*pos];

	switch (type)
	{
	case CHAR_IDENTIFIER:
		while (char_types[*pos] == CHAR_IDENTIFIER) ++pos;
		*src = pos;
		out.str.len = pos - out.str.ptr;
		// slight optimization as most keywords and operators are short
		if (out.str.len > MAX_KEYWORD_LENGTH)
		{
			out.type = TOK_IDENTIFIER;
			return out;
		}
		// else table lookup
		break;
		
	case CHAR_SEPARATOR:
		*src = ++pos;
		out.str.len = 1;
		out.type = ctok_types[*out.str.ptr];
		return out;

	case CHAR_OPERATOR:
		while (char_types[*pos] == CHAR_OPERATOR) ++pos;
		*src = pos;
		out.str.len = pos - out.str.ptr;
		if (out.str.len == 1)
		{
			out.type = ctok_types[*out.str.ptr];
			return out;
		}

		// else table lookup
		break;

	case CHAR_DIGIT:
		out.type = TOK_NUM_LITERAL;
		bool decimal;
		decimal = false;
		pos += 1;
		while (*pos)
		{
			if (char_types[*pos] != CHAR_DIGIT)
			{
				if (*pos == '.')
				{
					if (decimal) break;
					decimal = true;
				}
				else
				{
					break;
				}
			}
			pos += 1;
		}

		*src = pos;

		out.str.len = pos - out.str.ptr;
		return out;

	case CHAR_QUOTE:
		printf("First character: %c\n", out.str.ptr[0]);
		// get end of string
		pos += 1;
		// got till non-escaped end of string
		while (pos[0] != out.str.ptr[0] && pos[-1] != '\\') ++pos;
		pos += 1;
		*src = pos;
		out.str.len = pos - out.str.ptr;

		if (out.str.ptr[0] == '\'') out.type = TOK_CHAR_LITERAL;
		else if (out.str.ptr[0] == '\"') out.type = TOK_STR_LITERAL;

		return out;

	default:
		out.type = TOK_ERROR;
		return out;
	}

	char tmp[MAX_KEYWORD_LENGTH + 1];

	// table lookup
	for (int i = 0; i < out.str.len; ++i)
	{
		tmp[i] = out.str.ptr[i];
	}

	tmp[out.str.len] = 0;
	out.type = chartbl_get(tok_types, tmp);

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

	return out;
}

toklist_t *lex(char *src)
{
	toklist_t *out = toklist_create();

	token_t tok = lex_next_token(&src);
	while (1)
	{
		if (tok.type == TOK_NO_TYPE)
		{
			puts("Token has no type");
			break;
		}
		else if (tok.type == TOK_ERROR)
		{
			puts("Token was error type");
			break;
		}
		toklist_push(out, tok);
		tok = lex_next_token(&src);
	}

	return out;
}
