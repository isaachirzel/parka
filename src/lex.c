// main header
#include <grackle/lex.h>

// local includes
#include <grackle/chartbl.h>

// standard libary
#include <stdlib.h>


char char_types[128];
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
	char_types['('] = CHAR_SEPARATOR;
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
	for (int i = 33; i < sizeof(char_types); ++i)
	{
		if (char_types[i] == CHAR_NO_TYPE) char_types[i] = CHAR_INVALID;
	}

	// initializing token types
	tok_types = chartbl_create();
	puts("RETURN");
	chartbl_set(tok_types, "return", TOK_RETURN);
	puts("=");
	chartbl_set(tok_types, "=", TOK_ASSIGN);
	puts("+=");
	chartbl_set(tok_types, "+=", TOK_ADD_ASSIGN);
}

void lex_cleanup()
{
	chartbl_destroy(tok_types);
}

token_t lex_next_token(const char **src)
{
	token_t out;
	out.type = TOK_NO_TYPE;
	const char *pos = *src;
	// skip to next visible character
	while (*pos < 33)
	{
		if (*pos == 0) return out;
		++pos;
	}
	const char *start = pos;
	// get type of charcter
	char type = char_types[*pos];

	// string and char literals
	if (type == CHAR_QUOTE)
	{
		// get end of string
		char end = *pos;
		pos += 1;
		// got till non-escaped end of string
		while (pos[0] != end && pos[-1] != '\\') ++pos;
		pos += 1;
	}
	// number literals
	else if (type == CHAR_DIGIT)
	{
		bool decimal = false;
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
	}
	// normal tokens
	else
	{
		// go till char is of different type
		while (char_types[*pos] == type) ++pos;
	}

	// initializing token
	out.str.ptr = start;
	out.str.len = pos - start;

	// figuring out token type

	// for storing token for comparisons
	char tmp[MAX_KEYWORD_LENGTH + 1];

	switch (type)
	{
	case CHAR_IDENTIFIER:
		// slight optimization as most keywords and operators are short
		if (out.str.len > MAX_KEYWORD_LENGTH)
		{
			out.type = TOK_IDENTIFIER;
			break;
		}
		// inentional fall-through
	case CHAR_SEPARATOR:
	case CHAR_OPERATOR:
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
		// table lookup
		break;

	case CHAR_DIGIT:
		out.type = TOK_NUM_LITERAL;
		break;

	case CHAR_QUOTE:
		if (*start == '\'') out.type = TOK_CHAR_LITERAL;
		else if (*start == '\"') out.type = TOK_STR_LITERAL;
		break;

	default:
		out.type = TOK_ERROR;
		break;
	}


	*src = pos;
	return out;
}

toklist_t *lex(const char *src)
{
	toklist_t *out = toklist_create();

	token_t tok = lex_next_token(&src);
	while (tok.type != TOK_NO_TYPE)
	{
		toklist_push(out, tok);
		tok = lex_next_token(&src);
	}

	return out;
}
