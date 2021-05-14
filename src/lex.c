// main header
#include <grackle/lex.h>

// standard libary
#include <stdlib.h>

char char_types[128];
const char *tokens[] = {
	"int"
};

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
	char_types['\''] = CHAR_LITERAL;
	char_types['\"'] = CHAR_LITERAL;

	// making the rest of visible characters invalid
	for (int i = 33; i < sizeof(char_types); ++i)
	{
		if (char_types[i] == CHAR_NO_TYPE) char_types[i] = CHAR_INVALID;
	}

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
	if (type == CHAR_LITERAL)
	{
		// get end of string
		char end = *pos;
		pos += 1;
		// got till non-escaped end of string
		while (pos[0] != end && pos[-1] != '\\') ++pos;
		pos += 1;
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
	out.type = TOK_IDENTIFIER;	// change later

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
