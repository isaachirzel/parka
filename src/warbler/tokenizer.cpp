#include <warbler/tokenizer.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstring>
#include <cstdlib>
#include <unordered_map>

namespace warbler
{
	struct Location
	{
		const char * filename;
		const char *ptr;
		usize line;
		usize col;
	};

	std::ostream& error_out(const Location& location)
	{
		std::cout << location.filename << ':' << location.line << ':' << location.col;

		return error_out();
	}

	enum CharType
	{
		CHAR_INVALID,
		CHAR_WHITESPACE,
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
		{ "else", TOKEN_ELSE },
		{ "match", TOKEN_MATCH },
		{ "case", TOKEN_CASE },
		{ "struct", TOKEN_STRUCT },
		{ "union", TOKEN_UNION },
		{ "enum", TOKEN_ENUM },
		{ "true", TOKEN_TRUE },
		{ "false", TOKEN_FALSE },
		{ "import", TOKEN_IMPORT },
		{ "export", TOKEN_EXPORT }
	};

	CharType char_types[256];

	void init_char_types()
	{
		char_types[0] = CHAR_NULL;

		for (usize i = 1; i <= ' '; ++i)
			char_types[i] = CHAR_WHITESPACE;

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

	#pragma message("figure out find_next_location() for multiline strings")

	static Location get_end_of_token_location(const Token& token)
	{
		return Location
		{
			token.filename(),
			token.text().data() + token.text().size(),
			token.line(),
			token.col() + token.text().size()
		};
	}

	static Location find_next_location(const Location& last_location)
	{
		auto location = last_location;

		while (true)
		{
			auto character = *location.ptr;

			if (character == '\0' || character > ' ')
				break;

			location.ptr += 1;
			location.col += 1;

			if (character == '\n')
			{
				location.line += 1;
				location.col = 0;
			}
		}

		return location;
	}

	static inline bool is_char_alphanumeric(char c)
	{
		CharType type = get_char_type(c);

		return type == CHAR_IDENTIFIER || type == CHAR_DIGIT;
	}

	static Result<Token> get_identifier_token(const Location& location)
	{
		const char *pos = location.ptr + 1;

		while (is_char_alphanumeric(*pos))
			pos += 1;

		StringView text(location.ptr, pos - location.ptr);
		auto type = get_token_type(text);

		return Token(text, location.filename, location.line, location.col, type);
	}

	static Result<Token> get_separator_token(const Location& location)
	{
		StringView text(location.ptr, 1);

		TokenType type;
		switch (text[0])
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
				error_out(location) << "invalid character given for separator: " << location.ptr[0] << std::endl;
				return ERROR_ARGUMENT;
		}

		return Token(text, location.filename, location.line, location.col, type);
	}

	static Result<Token> get_digit_token(const Location& location)
	{
		const char *pos = location.ptr;
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

		StringView text(location.ptr, pos - location.ptr);

		if (decimal_count > 1)
		{
			error_out(location) << "only one decimal is allowed in float literal: " << text << std::endl;
			return ERROR_ARGUMENT;
		}

		auto type = decimal_count > 0
			? TOKEN_FLOAT_LITERAL
			: TOKEN_INTEGER_LITERAL;

		return Token(text, location.filename, location.line, location.col, type);
	}

	static Result<Token> get_dot_token(const Location& location)
	{
		const char *pos = location.ptr;

		if (get_char_type(pos[1]) == CHAR_DIGIT)
			return get_digit_token(location);

		pos += 1;

		while (get_char_type(*pos) == CHAR_DOT)
			pos += 1;

		StringView text(location.ptr, pos - location.ptr);

		TokenType type;

		switch (text.size())
		{
			case 1:
				type = TOKEN_DOT;
				break;

			case 3:
				type = TOKEN_ELIPSIS;
				break;

			default:
				error_out(location) << "invalid dot token: " << text << std::endl;
				return ERROR_ARGUMENT;
		}

		return Token(text, location.filename, location.line, location.col, type);
	}

	static Token get_plus_operator(const Location& location)
	{
		TokenType type;
		usize length;

		switch (location.ptr[1])
		{
			case '+':
				type = TOKEN_INCREMENT;
				length = 2;
				break;

			case '=':
				type = TOKEN_ADD_ASSIGN;
				length = 2;
				break;

			default:
				type = TOKEN_PLUS;
				length = 1;
				break;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_hyphen_operator(const Location& location)
	{
		TokenType type;
		usize length;

		switch (location.ptr[1])
		{
			case '-': // --
				type = TOKEN_DECREMENT;
				length = 2;
				break;

			case '=': // -=
				type = TOKEN_SUBTRACT_ASSIGN;
				length = 2;
				break;

			case '>': // ->
				type = TOKEN_SINGLE_ARROW;
				length = 2;
				break;

			default: // -
				type = TOKEN_MINUS;
				length = 1;
				break;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_asterisk_operator(const Location& location)
	{
		TokenType type;
		usize length;
		
		switch (location.ptr[1])
		{
			case '*': // **
				type = TOKEN_POW;
				length = 2;
				break;

			case '=': // *=
				type = TOKEN_MULTIPLY_ASSIGN;
				length = 2;
				break;

			default: // *
				type = TOKEN_ASTERISK;
				length = 1;
				break;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_slash_operator(const Location& location)
	{
		TokenType type;
		usize length;

		if (location.ptr[1] == '=')
		{
			type = TOKEN_DIVIDE_ASSIGN;
			length = 2;
		}
		else
		{
			type = TOKEN_SLASH;
			length = 1;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_langbrack_operator(const Location& location)
	{
		TokenType type;
		usize length;

		switch (location.ptr[1])
		{
			case '<': // <<
				if (location.ptr[2] == '=') // <<=
				{
					type = TOKEN_LSHIFT_ASSIGN;
					length = 3;
				}
				else
				{
					type = TOKEN_LSHIFT;
					length = 2;
				}
				break;

			case '=': // <=
				type = TOKEN_LESS_OR_EQUAL;
				length = 2;
				break;

			default: // <
				type = TOKEN_LESS_THAN;
				length = 1;
				break;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_rangbrack_operator(const Location& location)
	{
		TokenType type;
		usize length;

		switch (location.ptr[1])
		{
			case '>': // >>
				if (location.ptr[2] == '=') // >>=
				{
					type = TOKEN_RSHIFT_ASSIGN;
					length = 3;
				}
				else
				{
					type = TOKEN_RSHIFT;
					length = 2;
				}
				break;

			case '=': // <=
				type = TOKEN_GREATER_OR_EQUAL;
				length = 2;
				break;

			default: // >
				type = TOKEN_GREATER_THAN;
				length = 1;
				break;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_ampersand_operator(const Location& location)
	{
		TokenType type;
		usize length;

		if (location.ptr[1] == '=')
		{
			type = TOKEN_BITAND_ASSIGN;
			length = 2;
		}
		else if (location.ptr[1] == '&')
		{
			type = TOKEN_BOOLEAN_AND;
			length = 2;
		}
		else
		{
			type = TOKEN_AMPERSAND;
			length = 1;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}
	
	static Token get_pipeline_operator(const Location& location)
	{
		TokenType type;
		usize length;

		if (location.ptr[1] == '=')
		{
			type = TOKEN_BITOR_ASSIGN;
			length = 2;
		}
		else if (location.ptr[1] == '|')
		{
			type = TOKEN_BOOLEAN_OR;
			length = 2;
		}
		else
		{
			type = TOKEN_PIPELINE;
			length = 1;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_carrot_operator(const Location& location)
	{
		TokenType type;
		usize length;

		if (location.ptr[1] == '=')
		{
			type = TOKEN_BITXOR_ASSIGN;
			length = 2;
		}
		else
		{
			type = TOKEN_CARROT;
			length = 1;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_equals_operator(const Location& location)
	{
		TokenType type;
		usize length;

		switch (location.ptr[1])
		{
			case '=':
				type = TOKEN_EQUALS;
				length = 2;
				break;

			case '>':
				type = TOKEN_DOUBLE_ARROW;
				length = 2;
				break;

			default:
				type = TOKEN_ASSIGN;
				length = 1;
				break;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_exclamation_operator(const Location& location)
	{
		TokenType type;
		usize length;

		if (location.ptr[1] == '=')
		{
			type = TOKEN_NOT_EQUALS;
			length = 2;
		}
		else
		{
			type = TOKEN_BOOLEAN_NOT;
			length = 1;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_question_operator(const Location& location)
	{
		TokenType type;
		usize length;

		if (location.ptr[1] == '?')
		{
			type = TOKEN_OPTION;
			length = 2;
		}
		else
		{
			type = TOKEN_QUESTION;
			length = 1;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_modulus_operator(const Location& location)
	{
		TokenType type;
		usize length;

		if (location.ptr[1] == '=')
		{
			type = TOKEN_MODULUS_ASSIGN;
			length = 2;
		}
		else
		{
			type = TOKEN_MODULUS;
			length = 1;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Token get_colon_operator(const Location& location)
	{
		TokenType type;
		usize length;

		if (location.ptr[1] == ':')
		{
			type = TOKEN_SCOPE;
			length = 2;
		}
		else
		{
			type = TOKEN_COLON;
			length = 1;
		}

		return Token(StringView(location.ptr, length), location.filename, location.line, location.col, type);
	}

	static Result<Token> get_operator_token(const Location& location)
	{
		switch (location.ptr[0])
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
				break;
		}

		error_out(location) << "invalid character given in operator: " << location.ptr[0] << std::endl;
		return ERROR_ARGUMENT;
	}

	static inline bool is_end_of_text_literal(const char *pos, char terminal_char)
	{
		return pos[0] == terminal_char && pos[-1] != '\\';
	}

	static Result<Token> get_quote_token(const Location& location)
	{	
		char terminal_char = location.ptr[0];

		const char *pos = location.ptr + 1;
		while (*pos && !is_end_of_text_literal(pos, terminal_char))
			++pos;

		if (*pos == '\0')
		{
			error_out(location) << "unterminated string literal: " << location.ptr << std::endl;
			return ERROR_ARGUMENT;
		}

		pos += 1;

		TokenType type;
		StringView text(location.ptr, pos - location.ptr);

		if (text[0] == '\'')
		{
			type = TOKEN_CHAR_LITERAL;
		}
		else
		{
			type = TOKEN_STRING_LITERAL;
		}
			
		return Token(text, location.filename, location.line, location.col, type);
	}

	static Result<Token> get_next_token(const Location& location)
	{
		auto type = get_char_type(location.ptr[0]);

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
				error_out(location) << "invalid character in source file: " << location.ptr[0]
					<< ", integer value: (" << (int)location.ptr[0] << ")" << std::endl; 
				return ERROR_ARGUMENT;
		}

		return Token(StringView(location.ptr, 0), location.filename, location.line, location.col, TOKEN_END_OF_FILE);
	}

	Result<std::vector<Token>> tokenize(const char *filename, const char *src)
	{	
		std::vector<Token> out;

		out.reserve(10);

		auto location = Location { filename, src, 0, 0 };

		do
		{
			location = find_next_location(location);

			if (out.size() == out.capacity())
				out.reserve(out.size() * 2);

			auto res = get_next_token(location);

			if (res.has_error())
				return res.error();

			out.emplace_back(res.unwrap());
			location = get_end_of_token_location(out.back());
		}
		while (out.back().type() != TOKEN_END_OF_FILE);

		for (const auto& token : out)
		{
			std::cout << token.line() << ':' << token.col() << " " << token << std::endl;
		}

		return out;
	}
}
