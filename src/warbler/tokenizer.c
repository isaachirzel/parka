#include <warbler/tokenizer.h>

// local includes

// standard libary
#include <string.h>

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

bool is_lexer_initialized = false;

std::unordered_map<std::string_view, Token::Type> token_types;
Token::Type char_token_types[CHAR_TYPE_COUNT];
CharType char_types[CHAR_TYPE_COUNT];


void initialize()
{
	if (_is_lexer_initialized)
		return;

	// setting up identifier characters
	char_types['_'] = CHAR_IDENTIFIER;
	for (unsigned i = 'a'; i <= 'z'; ++i)
		char_types[i] = CHAR_IDENTIFIER;
	for (unsigned i = 'A'; i <= 'Z'; ++i)
		char_types[i] = CHAR_IDENTIFIER;
	for (unsigned i = '0'; i <= '9'; ++i)
		char_types[i] = CHAR_DIGIT;

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

	// setting up single character token types

	// Assignment
	char_token_types['='] = TOK_ASSIGN;

	// Separators
	char_token_types['('] = TOK_LPAREN;
	char_token_types[')'] = TOK_RPAREN;
	char_token_types['['] = TOK_LBRACK;
	char_token_types[']'] = TOK_RBRACK;
	char_token_types['{'] = TOK_LBRACE;
	char_token_types['}'] = TOK_RBRACE;
	char_token_types['.'] = TOK_DOT;
	char_token_types[','] = TOK_COMMA;
	char_token_types[';'] = TOK_SEMICOLON;

	// Operators
	char_token_types['*'] = TOK_ASTERISK;
	char_token_types['/'] = TOK_SLASH;
	char_token_types['+'] = TOK_PLUS;
	char_token_types['-'] = TOK_MINUS;
	char_token_types['<'] = TOK_LANGBRACK;
	char_token_types['>'] = TOK_RANGBRACK;
	char_token_types[':'] = TOK_COLON;
	char_token_types['&'] = TOK_AMPERSAND;
	char_token_types['|'] = TOK_PIPELINE;
	char_token_types['^'] = TOK_CARROT;

	// keywords
	chartbl_set(tok_types, "func", TOK_FUNC);
	chartbl_set(tok_types, "var", TOK_VAR);
	chartbl_set(tok_types, "type", TOK_TYPE);

	chartbl_set(tok_types, "return", TOK_RETURN);
	chartbl_set(tok_types, "for", TOK_FOR);
	chartbl_set(tok_types, "while", TOK_WHILE);
	chartbl_set(tok_types, "loop", TOK_LOOP);
	chartbl_set(tok_types, "continue", TOK_CONTINUE);
	chartbl_set(tok_types, "break", TOK_BREAK);
	chartbl_set(tok_types, "if", TOK_IF);
	chartbl_set(tok_types, "else", TOK_ELSE);
	chartbl_set(tok_types, "switch", TOK_SWITCH);
	chartbl_set(tok_types, "case", TOK_CASE);

	// typenames
	chartbl_set(tok_types, "struct", TOK_STRUCT);
	chartbl_set(tok_types, "union", TOK_UNION);
	chartbl_set(tok_types, "enum", TOK_ENUM);
	chartbl_set(tok_types, "true", TOK_TRUE);
	chartbl_set(tok_types, "false", TOK_FALSE);

	// operators
	_token_types["++"] = TOK_INCREMENT;
	_token_types["--"] = TOK_DECREMENT;
	_token_types["**"] = TOK_POW;
	_token_types["&&"] = TOK_AND;
	_token_types["||"] = TOK_OR;
	_token_types["=="] = TOK_EQUALS;
	_token_types["!="] = TOK_NEQUALS;
	_token_types[">="] = TOK_GTOET;
	_token_types["<="] = TOK_LTOET;
	_token_types[">>"] = TOK_RSHIFT;
	_token_types["<<"] = TOK_LSHIFT;
	_token_types["->"] = TOK_SINGLE_ARROW;
	_token_types["=>"] = TOK_DOUBLE_ARROW;

	// assign operators
	_token_types["+="] = TOK_ADD_ASSIGN;
	_token_types["+="] = TOK_ADD_ASSIGN;
	_token_types["-="] = TOK_SUB_ASSIGN;
	_token_types["*="] = TOK_MUL_ASSIGN;
	_token_types["/="] = TOK_DIV_ASSIGN;
	_token_types["%="] = TOK_MOD_ASSIGN;

	// scope
	_token_types["export"]= TOK_EXPORT;
	_token_types["import"] = TOK_IMPORT;
	_token_types["::"] = TOK_SCOPE;

	_is_lexer_initialized = true;
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
