// main header
#include <grackle/lexer.h>

// local includes
#include <grackle/container/chartbl.h>
#include <grackle/log.h>

// standard libary
#include <stdlib.h>

// lookup-table for character-types
char char_types[128];
// lookup-table for single-character token-types
char ctok_types[128];
chartbl_t *tok_types = NULL;


void lex_error(token_t *token)
{
	log_error_prompt(token->line, token->col);
	fputs("invalid token '", stderr);
	string_fputs(&token->str, stderr);
	fputs("'\n", stderr);
}


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

	// dot character
	char_types['.'] = CHAR_DOT;

	// setting up operator characters
	char_types['!'] = CHAR_OPERATOR;
	char_types['@'] = CHAR_OPERATOR;
	char_types['#'] = CHAR_OPERATOR;
	char_types['$'] = CHAR_OPERATOR;
	char_types['%'] = CHAR_OPERATOR;
	char_types['^'] = CHAR_OPERATOR;
	char_types['&'] = CHAR_OPERATOR;
	char_types['*'] = CHAR_OPERATOR;
	char_types['-'] = CHAR_OPERATOR;
	char_types['='] = CHAR_OPERATOR;
	char_types['|'] = CHAR_OPERATOR;
	char_types['+'] = CHAR_OPERATOR;
	char_types['<'] = CHAR_OPERATOR;
	char_types['>'] = CHAR_OPERATOR;
	char_types['?'] = CHAR_OPERATOR;
	char_types['/'] = CHAR_OPERATOR;
	char_types[':'] = CHAR_OPERATOR;

	// setting literal types
	char_types['\''] = CHAR_QUOTE;
	char_types['\"'] = CHAR_QUOTE;

	// making the rest of visible characters invalid
	for (unsigned i = 33; i < sizeof(char_types); ++i)
	{
		if (char_types[i] == CHAR_NO_TYPE) char_types[i] = CHAR_INVALID;
	}

	// setting up single character token types

	// Assignment
	ctok_types['='] = TOK_ASSIGN;

	// Separators
	ctok_types['('] = TOK_LPAREN;
	ctok_types[')'] = TOK_RPAREN;
	ctok_types['['] = TOK_LBRACK;
	ctok_types[']'] = TOK_RBRACK;
	ctok_types['{'] = TOK_LBRACE;
	ctok_types['}'] = TOK_RBRACE;
	ctok_types['.'] = TOK_DOT;
	ctok_types[','] = TOK_COMMA;
	ctok_types[';'] = TOK_SEMICOLON;

	// Operators
	ctok_types['*'] = TOK_ASTERISK;
	ctok_types['/'] = TOK_SLASH;
	ctok_types['+'] = TOK_PLUS;
	ctok_types['-'] = TOK_MINUS;
	ctok_types['<'] = TOK_LANGBRACK;
	ctok_types['>'] = TOK_RANGBRACK;
	ctok_types[':'] = TOK_COLON;
	ctok_types['&'] = TOK_AMPERSAND;
	ctok_types['|'] = TOK_PIPELINE;
	ctok_types['^'] = TOK_CARROT;

	// initializing token types
	tok_types = chartbl_create();
	chartbl_set(tok_types, "return", TOK_RETURN);
	chartbl_set(tok_types, "+=", TOK_ADD_ASSIGN);
	chartbl_set(tok_types, "func", TOK_FUNC);
	chartbl_set(tok_types, "var", TOK_VAR);

	// typenames
	chartbl_set(tok_types, "i8", TOK_TYPE_I8);
	chartbl_set(tok_types, "i16", TOK_TYPE_I16);
	chartbl_set(tok_types, "i32", TOK_TYPE_I32);
	chartbl_set(tok_types, "i64", TOK_TYPE_I64);

	chartbl_set(tok_types, "u8", TOK_TYPE_U8);
	chartbl_set(tok_types, "u16", TOK_TYPE_U16);
	chartbl_set(tok_types, "u32", TOK_TYPE_U32);
	chartbl_set(tok_types, "u64", TOK_TYPE_U64);

	chartbl_set(tok_types, "f32", TOK_TYPE_F32);
	chartbl_set(tok_types, "f64", TOK_TYPE_F64);
	
	chartbl_set(tok_types, "str", TOK_TYPE_STR);

	// operators
	chartbl_set(tok_types, "**", TOK_SQRT);
	chartbl_set(tok_types, "&&", TOK_AND);
	chartbl_set(tok_types, "||", TOK_OR);
	chartbl_set(tok_types, "==", TOK_EQUALS);
	chartbl_set(tok_types, "!=", TOK_NEQUALS);
	chartbl_set(tok_types, ">=", TOK_GTOET);
	chartbl_set(tok_types, "<=", TOK_LTOET);
	chartbl_set(tok_types, ">>", TOK_RSHIFT);
	chartbl_set(tok_types, "<<", TOK_LSHIFT);
	chartbl_set(tok_types, "->", TOK_SINGLE_ARROW);
	chartbl_set(tok_types, "=>", TOK_DOUBLE_ARROW);
}


void lex_cleanup()
{
	chartbl_destroy(tok_types);
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
			out.type = ctok_types[*out.str.ptr];
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
				out.type = ctok_types[*out.str.ptr];
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

	goto finish;
}

toklist_t *lex(char *src)
{
	toklist_t *out = toklist_create();

	token_t tok = lex_next_token(&src, 1, 1);
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
