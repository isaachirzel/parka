// main header
#include <grackle/lexer.h>

// local includes

// standard libary
#include <string.h>

#define CHAR_TYPE_COUNT (128)

namespace grackle::lexer
{
	// lookup-table for character-types
	bool is_lexer_initialized = false;
	std::unordered_map<std::string_view, Token::Type> token_types;
	Token::Type char_token_types[CHAR_TYPE_COUNT];
	CharType char_types[CHAR_TYPE_COUNT];


	void initialize()
	{
		if (_is_lexer_initialized)
			return;

		// setting up identifier characters
		char_types['_'] = CharType::IDENTIFIER;
		for (unsigned i = 'a'; i <= 'z'; ++i)
			char_types[i] = CharType::IDENTIFIER;
		for (unsigned i = 'A'; i <= 'Z'; ++i)
			char_types[i] = CharType::IDENTIFIER;
		for (unsigned i = '0'; i <= '9'; ++i)
			char_types[i] = CharType::DIGIT;

		// setting up separator characters
		char_types['('] = CharType::SEPARATOR;
		char_types[')'] = CharType::SEPARATOR;
		char_types['['] = CharType::SEPARATOR;
		char_types[']'] = CharType::SEPARATOR;
		char_types['{'] = CharType::SEPARATOR;
		char_types['}'] = CharType::SEPARATOR;
		char_types[';'] = CharType::SEPARATOR;
		char_types[','] = CharType::SEPARATOR;

		// dot character
		char_types['.'] = CharType::DOT;

		// setting up operator characters
		char_types['!'] = CharType::OPERATOR;
		char_types['@'] = CharType::OPERATOR;
		char_types['#'] = CharType::OPERATOR;
		char_types['$'] = CharType::OPERATOR;
		char_types['%'] = CharType::OPERATOR;
		char_types['^'] = CharType::OPERATOR;
		char_types['&'] = CharType::OPERATOR;
		char_types['*'] = CharType::OPERATOR;
		char_types['-'] = CharType::OPERATOR;
		char_types['='] = CharType::OPERATOR;
		char_types['|'] = CharType::OPERATOR;
		char_types['+'] = CharType::OPERATOR;
		char_types['<'] = CharType::OPERATOR;
		char_types['>'] = CharType::OPERATOR;
		char_types['?'] = CharType::OPERATOR;
		char_types['/'] = CharType::OPERATOR;
		char_types[':'] = CharType::OPERATOR;

		// setting literal types
		char_types['\''] = CharType::QUOTE;
		char_types['\"'] = CharType::QUOTE;

		// setting up single character token types

		// Assignment
		char_token_types['='] = Token::Type::ASSIGN;

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
		chartbl_set(tok_types, "func", Token::Type::FUNC);
		chartbl_set(tok_types, "var", Token::Type::VAR);
		chartbl_set(tok_types, "type", Token::Type::TYPE);

		chartbl_set(tok_types, "return", Token::Type::RETURN);
		chartbl_set(tok_types, "for", Token::Type::FOR);
		chartbl_set(tok_types, "while", Token::Type::WHILE);
		chartbl_set(tok_types, "loop", Token::Type::LOOP);
		chartbl_set(tok_types, "continue", Token::Type::CONTINUE);
		chartbl_set(tok_types, "break", Token::Type::BREAK);
		chartbl_set(tok_types, "if", Token::Type::IF);
		chartbl_set(tok_types, "else", Token::Type::ELSE);
		chartbl_set(tok_types, "switch", Token::Type::SWITCH);
		chartbl_set(tok_types, "case", Token::Type::CASE);

		// typenames
		chartbl_set(tok_types, "struct", Token::Type::STRUCT);
		chartbl_set(tok_types, "union", Token::Type::UNION);
		chartbl_set(tok_types, "enum", Token::Type::ENUM);
		chartbl_set(tok_types, "true", Token::Type::TRUE);
		chartbl_set(tok_types, "false", Token::Type::FALSE);

		// operators
		_token_types["++"] = Token::Type::INCREMENT;
		_token_types["--"] = Token::Type::DECREMENT;
		_token_types["**"] = Token::Type::POW;
		_token_types["&&"] = Token::Type::AND;
		_token_types["||"] = Token::Type::OR;
		_token_types["=="] = Token::Type::EQUALS;
		_token_types["!="] = Token::Type::NEQUALS;
		_token_types[">="] = Token::Type::GTOET;
		_token_types["<="] = Token::Type::LTOET;
		_token_types[">>"] = Token::Type::RSHIFT;
		_token_types["<<"] = Token::Type::LSHIFT;
		_token_types["->"] = Token::Type::SINGLE_ARROW;
		_token_types["=>"] = Token::Type::DOUBLE_ARROW;

		// assign operators
		_token_types["+="] = Token::Type::ADD_ASSIGN;
		_token_types["+="] = Token::Type::ADD_ASSIGN;
		_token_types["-="] = Token::Type::SUB_ASSIGN;
		_token_types["*="] = Token::Type::MUL_ASSIGN;
		_token_types["/="] = Token::Type::DIV_ASSIGN;
		_token_types["%="] = Token::Type::MOD_ASSIGN;

		// scope
		_token_types["export"]= Token::Type::EXPORT;
		_token_types["import"] = Token::Type::IMPORT;
		_token_types["::"] = Token::Type::SCOPE;

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
}
