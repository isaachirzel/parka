#include <warbler/tokenizer.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstring>
#include <cstdlib>
#include <unordered_map>

namespace warbler
{
	enum CharType
	{
		CHAR_INVALID,
		CHAR_NULL,
		CHAR_IDENTIFIER,
		CHAR_SEPARATOR,
		CHAR_DOT,
		CHAR_DIGIT,
		CHAR_OPERATOR,
		CHAR_QUOTE
	};

	std::unordered_map<std::string, TokenType> token_types = 
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
		{ "then", TOKEN_THEN },
		{ "else", TOKEN_ELSE },
		{ "match", TOKEN_MATCH },
		{ "case", TOKEN_CASE },
		{ "struct", TOKEN_STRUCT },
		{ "union", TOKEN_UNION },
		{ "enum", TOKEN_ENUM },
		{ "true", TOKEN_TRUE },
		{ "false", TOKEN_FALSE },
		{ "import", TOKEN_IMPORT },
		{ "export", TOKEN_EXPORT },
		{ "public", TOKEN_PUBLIC },
		{ "private", TOKEN_PRIVATE }
	};

	CharType char_types[256];

	void init_char_types()
	{
		char_types[0] = CHAR_NULL;

		// setting up identifier characters
		char_types[(usize)'_'] = CHAR_IDENTIFIER;
		for (usize i = 'a'; i <= 'z'; ++i)
			char_types[i] = CHAR_IDENTIFIER;
		for (usize i = 'A'; i <= 'Z'; ++i)
			char_types[i] = CHAR_IDENTIFIER;
		for (usize i = '0'; i <= '9'; ++i)
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

	void tokenizer_init()
	{
		init_char_types();
	}

	#define TEMP_KEY_SIZE (1023)

	static TokenType get_token_type(const StringView& text)
	{
		auto iter = token_types.find(String(text));

		if (iter == token_types.end())
			return TOKEN_IDENTIFIER;

		return iter->second;
	}

	static inline CharType get_char_type(unsigned char c)
	{
		return char_types[(size_t)c];
	}

	static Location find_next_position(const Location& last_location)
	{
		const auto* pos = last_location.pos_ptr();
		usize line = last_location.line();
		usize col = last_location.col();

		while (true)
		{
			auto character = *pos;

			if (character == '\0' || character > ' ')
				break;

			pos += 1;
			col += 1;

			if (character == '\n')
			{
				line += 1;
				col = 0;
			}
		}

		return { last_location.filename(), last_location.src(), line, col, (usize)(pos - last_location.src()), 0 };
	}

	static inline bool is_char_alphanumeric(char c)
	{
		CharType type = get_char_type(c);

		return type == CHAR_IDENTIFIER || type == CHAR_DIGIT;
	}

	static Result<Token> get_identifier_token(const Location& location)
	{
		const char *start = location.pos_ptr();
		const char *pos = start + 1;

		while (is_char_alphanumeric(*pos))
			pos += 1;

		StringView text(start, pos - start);
		auto type = get_token_type(text);

		return Token(location, type, pos - start);
	}

	static Result<Token> get_separator_token(const Location& location)
	{
		TokenType type;
		switch (location[0])
		{
			case '(':
				type = TOKEN_LPAREN;
				break;

			case ')':
				type = TOKEN_RPAREN;
				break;

			case '[':
				type = TOKEN_LBRACK;
				break;

			case ']':
				type = TOKEN_RBRACK;
				break;

			case '{':
				type = TOKEN_LBRACE;
				break;

			case '}':
				type = TOKEN_RBRACE;
				break;

			case ',':
				type = TOKEN_COMMA;
				break;

			case ';':
				type = TOKEN_SEMICOLON;
				break;
			
			default:
				error_out(location) << "invalid character given for separator: " << location[0] << std::endl;
				return ERROR_ARGUMENT;
		}

		return Token(location, type, 1);
	}

	static Result<Token> get_digit_token(const Location& location)
	{
		const char * const start = location.pos_ptr();
		const char *pos = start;
		usize decimal_count = 0;

		while (true)
		{
			CharType type = get_char_type(*pos);

			if (type == CHAR_DOT)
			{
				decimal_count += 1;
			}
			else if (type != CHAR_DIGIT)
			{
				break;
			}

			pos += 1;
		}

		if (decimal_count > 1)
		{
			error_out(location) << "only one decimal is allowed in float literal";
			error_highlight(location);
			return ERROR_ARGUMENT;
		}

		auto type = decimal_count > 0
			? TOKEN_FLOAT_LITERAL
			: TOKEN_INTEGER_LITERAL;

		return Token(location, type, pos - start);
	}

	static Result<Token> get_dot_token(const Location& location)
	{
		const char * const start = location.pos_ptr();
		const char *pos = start;

		if (get_char_type(pos[1]) == CHAR_DIGIT)
			return get_digit_token(location);

		pos += 1;

		while (get_char_type(*pos) == CHAR_DOT)
			pos += 1;

		TokenType type;
		switch (location.length())
		{
			case 1:
				type = TOKEN_DOT;
				break;

			case 3:
				type = TOKEN_ELIPSIS;
				break;

			default:
				error_out(location) << "invalid token";
				error_highlight(location);
				return ERROR_ARGUMENT;
		}

		return Token(location, type, pos - start);
	}

	static Token get_plus_operator(const Location& location)
	{
		switch (location[1])
		{
			case '+':
				return Token(location, TOKEN_INCREMENT, 2);

			case '=':
				return Token(location, TOKEN_ADD_ASSIGN, 2);

			default:
				return Token(location, TOKEN_PLUS, 1);
		}
	}

	static Token get_hyphen_operator(const Location& location)
	{
		switch (location[1])
		{
			case '-': // --
				return Token(location, TOKEN_DECREMENT, 2);

			case '=': // -=
				return Token(location, TOKEN_SUBTRACT_ASSIGN, 2);

			case '>': // ->
				return Token(location, TOKEN_SINGLE_ARROW, 2);

			default: // -
				return Token(location, TOKEN_MINUS, 1);
		}
	}

	static Token get_asterisk_operator(const Location& location)
	{
		switch (location[1])
		{
			case '*': // **
				return Token(location, TOKEN_POW, 2);

			case '=': // *=
				return Token(location, TOKEN_MULTIPLY_ASSIGN, 2);

			default: // *
				return Token(location, TOKEN_ASTERISK, 1);
		}
	}

	static Token get_slash_operator(const Location& location)
	{
		if (location[1] == '=')
			return Token(location, TOKEN_DIVIDE_ASSIGN, 2);

		return Token(location, TOKEN_SLASH, 1);
	}

	static Token get_langbrack_operator(const Location& location)
	{
		switch (location[1])
		{
			case '<': // <<
				if (location[2] == '=') // <<=
					return Token(location, TOKEN_LSHIFT_ASSIGN, 3);

				return Token(location, TOKEN_LSHIFT, 2);

			case '=': // <=
				return Token(location, TOKEN_LESS_OR_EQUAL, 2);

			default: // <
				return Token(location, TOKEN_LESS_THAN, 1);
		}
	}

	static Token get_rangbrack_operator(const Location& location)
	{
		switch (location[1])
		{
			case '>': // >>
				if (location[2] == '=') // >>=
					return Token(location, TOKEN_RSHIFT_ASSIGN, 3);

				return Token(location, TOKEN_RSHIFT, 2);

			case '=': // <=
				return Token(location, TOKEN_GREATER_OR_EQUAL, 2);

			default: // >
				return Token(location, TOKEN_GREATER_THAN, 1);
		}
	}

	static Token get_ampersand_operator(const Location& location)
	{
		switch (location[0])
		{
			case '=':
				return Token(location, TOKEN_BITAND_ASSIGN, 2);

			case '&':
				return Token(location, TOKEN_BOOLEAN_AND, 2);

			default:
				return Token(location, TOKEN_AMPERSAND, 1);
		}
	}
	
	static Token get_pipeline_operator(const Location& location)
	{
		switch (location[1])
		{
			case '=':
				return Token(location, TOKEN_BITOR_ASSIGN, 2);

			case '|':
				return Token(location, TOKEN_BOOLEAN_OR, 2);

			default:
				return Token(location, TOKEN_PIPELINE, 1);
		}
	}

	static Token get_carrot_operator(const Location& location)
	{
		if (location[1] == '=')
			return Token(location, TOKEN_BITXOR_ASSIGN, 2);

		return Token(location, TOKEN_CARROT, 1);
	}

	static Token get_equals_operator(const Location& location)
	{
		switch (location[1])
		{
			case '=':
				return Token(location, TOKEN_EQUALS, 2);

			case '>':
				return Token(location, TOKEN_DOUBLE_ARROW, 2);

			default:
				return Token(location, TOKEN_ASSIGN, 1);
		}
	}

	static Token get_exclamation_operator(const Location& location)
	{
		if (location[1] == '=')
			return Token(location, TOKEN_NOT_EQUALS, 2);

		return Token(location, TOKEN_BOOLEAN_NOT, 1);
	}

	static Token get_question_operator(const Location& location)
	{
		if (location[1] == '?')		
			return Token(location, TOKEN_OPTION, 2);
	
		return Token(location, TOKEN_QUESTION, 1);
	}

	static Token get_modulus_operator(const Location& location)
	{
		if (location[1] == '=')
			return Token(location, TOKEN_MODULUS_ASSIGN, 2);
		
		return Token(location, TOKEN_MODULUS, 1);
	}

	static Token get_colon_operator(const Location& location)
	{
		switch (location[1])
		{
			case ':':
				return Token(location, TOKEN_SCOPE, 2);

			case '=':
				return Token(location, TOKEN_BECOME_ASSIGN, 2);

			default:
				return Token(location, TOKEN_COLON, 1);
		}
	}

	static Result<Token> get_operator_token(const Location& location)
	{
		switch (location[0])
		{
			case '+': // +, ++, +=
				return get_plus_operator(location);

			case '-': // -, --, -=, ->
				return get_hyphen_operator(location);

			case '*': // *, **, *=
				return get_asterisk_operator(location);

			case '/': // /, /=
				return get_slash_operator(location);

			case '<': // <, <<, <=
				return get_langbrack_operator(location);

			case '>': // >, >>, >=
				return get_rangbrack_operator(location);

			case '&': // &, &=
				return get_ampersand_operator(location);

			case '|': // |, |=
				return get_pipeline_operator(location);

			case '^': // ^, ^=
				return get_carrot_operator(location);

			case '=': // =, ==, =>
				return get_equals_operator(location);

			case '!': // !, !=
				return get_exclamation_operator(location);

			case '?': // ?, ??
				return get_question_operator(location);				

			case '%': // %, %=
				return get_modulus_operator(location);

			case ':': // :, ::
				return get_colon_operator(location);

			default:
				error_out(location) << "invalid character given in operator";
				error_highlight(location.with_length(1));
				return ERROR_ARGUMENT;
		}
	}

	static inline bool is_end_of_text_literal(const char *pos, char terminal_char)
	{
		return pos[0] == terminal_char && pos[-1] != '\\';
	}

	static Result<Token> get_quote_token(const Location& location)
	{	
		const char * const start = location.pos_ptr();
		char terminal_char = start[0];
		const char *pos = start + 1;

		while (*pos && !is_end_of_text_literal(pos, terminal_char))
			++pos;

		if (*pos == '\0')
		{
			error_out(location) << "unterminated string literal";
			error_highlight(location.with_length((usize)(pos - start)));
			return ERROR_ARGUMENT;
		}

		pos += 1;

		auto type = terminal_char == '\''
			? TOKEN_CHAR_LITERAL
			: TOKEN_STRING_LITERAL;
			
		return Token(location, type, pos - start);
	}

	static Result<Token> get_next_token(const Location& location)
	{
		auto type = get_char_type(location[0]);

		switch (type)
		{
			case CHAR_NULL:
				break;

			case CHAR_IDENTIFIER:
				return get_identifier_token(location);

			case CHAR_SEPARATOR:
				return get_separator_token(location);

			case CHAR_DOT:
				return get_dot_token(location);

			case CHAR_DIGIT:
				return get_digit_token(location);

			case CHAR_OPERATOR:
				return get_operator_token(location);

			case CHAR_QUOTE:
				return get_quote_token(location);

			case CHAR_INVALID:
				error_out(location) << "invalid character in source file: " << location[0]
					<< ", integer value: (" << (int)location[0] << ")";
				error_highlight(location.with_length(1));
				return ERROR_ARGUMENT;
		}

		return Token();
	}

	Result<std::vector<Token>> tokenize(const char *filename, const char *src)
	{	
		std::vector<Token> out;

		out.reserve(10);

		Location location(filename, src);

		do
		{
			location = find_next_position(location);

			if (out.size() == out.capacity())
				out.reserve(out.size() * 2);

			auto res = get_next_token(location);

			if (!res)
				return res.error();

			out.emplace_back(res.unwrap());
			location.offset(out.back().length());
		}
		while (out.back().type() != TOKEN_END_OF_FILE);

		return out;
	}
}
