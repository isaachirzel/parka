#include <warbler/lexicon/tokenizer.hpp>

// local headers
#include <warbler/util/print.hpp>

// standard headers
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <unordered_map>

#define MAX_KEYWORD_LENGTH	(15)

namespace warbler::lexicon
{
	using source::File;
	using source::Location;

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

	static CharType char_types[256];

	static inline bool _match_str(const char * const text, const char * const compare, const usize size)
	{
		for (usize i = 0; i < size; ++i)
		{
			if (text[i] != compare[i])
				return false;
		}

		return true;
	}

	#define match_str(text, compare) _match_str(text, compare, sizeof(compare))

	TokenType get_identifier_type(const char *text)
	{
		switch (text[0])
		{
			case 'b':
				if (match_str(text + 1, "reak"))
					return TOKEN_KEYWORD_BREAK;
				break;

			case 'c':
				if (text[1] == 'a')
				{
					if (match_str(text + 2, "se"))
						return TOKEN_KEYWORD_CASE;
				}
				else if (text[1] == 'o')
				{
					if (match_str(text + 2, "ntinue"))
						return TOKEN_KEYWORD_CONTINUE;
				}
				break;

			case 'e':
				switch (text[1])
				{
					case 'l':
						if (match_str(text + 2, "se"))
							return TOKEN_KEYWORD_ELSE;
						break;

					case 'n':
						if (match_str(text + 2, "um"))
							return TOKEN_KEYWORD_ENUM;
						break;

					case 'x':
						if (match_str(text + 2, "port"))
							return TOKEN_KEYWORD_EXPORT;
						break;

					default:
						return TOKEN_IDENTIFIER;
				}
				break;

			case 'f':
				switch (text[1])
				{
					case 'a':
						if (match_str(text + 2, "lse"))
							return TOKEN_KEYWORD_FALSE;
						break;
						
					case 'o':
						if (text[2] == 'r' && text[3] == '\0')
							return TOKEN_KEYWORD_FOR;
						break;

					case 'u':
						if (match_str(text + 2, "nction"))
							return TOKEN_KEYWORD_FUNCTION;
						break;

					default:
						return TOKEN_IDENTIFIER;
				}
				break;

			case 'i':
				if (text[1] == 'f')
				{
					if (text[2] == '\0')
						return TOKEN_KEYWORD_IF;
				}
				else if (text[1] == 'm')
				{
					if (match_str(text + 2, "port"))
						return TOKEN_KEYWORD_IMPORT;
				}
				break;

			case 'l':
				if (match_str(text + 1, "oop"))
					return TOKEN_KEYWORD_LOOP;
				break;

			case 'm':
				if (text[1] == 'a')
				{
					if (match_str(text + 2, "tch"))
						return TOKEN_KEYWORD_MATCH;
				}
				else if (text[1] == 'u')
				{
					if (match_str(text + 2, "t"))
						return TOKEN_KEYWORD_MUT;
				}
				break;

			case 'p':
				if (text[1] == 'r')
				{
					if (match_str(text + 2, "ivate"))
						return TOKEN_KEYWORD_PRIVATE;
				}
				else if (text[1] == 'u')
				{
					if (match_str(text + 2, "blic"))
						return TOKEN_KEYWORD_PUBLIC;
				}
				break;

			case 'r':
				if (match_str(text + 1, "eturn"))
					return TOKEN_KEYWORD_RETURN;
				break;

			case 's':
				if (match_str(text + 1, "truct"))
					return TOKEN_KEYWORD_STRUCT;
				break;

			case 't':
				switch (text[1])
				{
					case 'h':
						if (match_str(text + 2, "en"))
							return TOKEN_KEYWORD_THEN;
						break;

					case 'r':
						if (match_str(text + 2, "ue"))
							return TOKEN_KEYWORD_TRUE;
						break;

					case 'y':
						if (match_str(text + 2, "pe"))
							return TOKEN_KEYWORD_TYPE;
						break;
				}
				break;

			case 'u':
				if (match_str(text + 1, "nion"))
					return TOKEN_KEYWORD_UNION;
				break;

			case 'v':
				if (match_str(text + 1, "ar"))
					return TOKEN_KEYWORD_VAR;
				break;

			case 'w':
				if (match_str(text + 1, "hile"))
					return TOKEN_KEYWORD_WHILE;
				break;
				
			default:
				break;
		}

		return TOKEN_IDENTIFIER;
	}
	


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

	void init_tokenizer()
	{
		init_char_types();
	}

	static inline CharType get_char_type(unsigned char c)
	{
		return char_types[(size_t)c];
	}

	static usize find_next_position(const File& file, usize pos)
	{		
		while (true)
		{
			auto character = file[pos];

			if (character == '\0' || character > ' ')
				break;

			pos += 1;
		}

		return pos;
	}

	static inline bool is_char_alphanumeric(char c)
	{
		CharType type = get_char_type(c);

		return type == CHAR_IDENTIFIER || type == CHAR_DIGIT;
	}

	static Token get_identifier_token(const File& file, const usize start_pos)
	{
		auto pos = start_pos + 1;

		while (is_char_alphanumeric(file[pos]))
			pos += 1;

		usize length = pos - start_pos;

		return Token(Location(file, start_pos, length), TOKEN_IDENTIFIER);
	}

	static Token get_separator_token(const File& file, const usize start_pos)
	{
		TokenType type;

		switch (file[start_pos])
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
				throw std::runtime_error("invalid chracter was passed to get_separator_token: '" + String(1, file[start_pos]) + "'");
		}

		return Token(Location(file, start_pos, 1), type);
	}

	static Result<Token> get_digit_token(const File& file, const usize start_pos)
	{
		auto pos = start_pos;
		usize decimal_count = 0;

		while (true)
		{
			CharType type = get_char_type(file[pos]);

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

		auto length = pos - start_pos;

		if (decimal_count > 1)
		{
			auto text = file.get_snippet(start_pos, length);
			print_error(text, "only one decimal is allowed in float literal");
			return {};
		}

		auto type = decimal_count > 0
			? TOKEN_FLOAT_LITERAL
			: TOKEN_INTEGER_LITERAL;

		return Token(Location(file, start_pos, length), type);
	}

	static Result<Token> get_dot_token(const File& file, const usize start_pos)
	{
		if (get_char_type(file[start_pos + 1]) == CHAR_DIGIT)
			return get_digit_token(file, start_pos);

		usize pos = start_pos + 1;

		while (get_char_type(file[pos]) == CHAR_DOT)
			pos += 1;

		auto length = pos - start_pos;

		TokenType type;

		switch (length)
		{
			case 1:
				type = TOKEN_DOT;
				break;

			case 3:
				type = TOKEN_ELIPSIS;
				break;

			default:
			{
				auto text = file.get_snippet(start_pos, length);
				print_error(text, "invalid token, expected '.' or '...'");
				return {};
			}
		}

		return Token(Location(file, start_pos, length), type);
	}

	static Token get_plus_operator(const File& file, const usize start_pos)
	{
		switch (file[1])
		{
			case '=':
				return Token(Location(file, start_pos, 2), TOKEN_ADD_ASSIGN);

			default:
				return Token(Location(file, start_pos, 1), TOKEN_PLUS);
		}
	}

	static Token get_hyphen_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '=': // -=
				return Token(Location(file, start_pos, 2), TOKEN_SUBTRACT_ASSIGN);

			case '>': // ->
				return Token(Location(file, start_pos, 2), TOKEN_SINGLE_ARROW);

			default: // -
				return Token(Location(file, start_pos, 1), TOKEN_MINUS);
		}
	}

	static Token get_asterisk_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '*': // **
				return Token(Location(file, start_pos, 2), TOKEN_POW);

			case '=': // *=
				return Token(Location(file, start_pos, 2), TOKEN_MULTIPLY_ASSIGN);

			default: // *
				return Token(Location(file, start_pos, 1), TOKEN_ASTERISK);
		}
	}

	static Token get_slash_operator(const File& file, const usize start_pos)
	{
		if (file[start_pos + 1] == '=')
			return Token(Location(file, start_pos, 2), TOKEN_DIVIDE_ASSIGN);

		return Token(Location(file, start_pos, 1), TOKEN_SLASH);
	}

	static Token get_langbrack_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '<': // <<
				if (file[start_pos + 2] == '=') // <<=
					return Token(Location(file, start_pos, 3), TOKEN_LSHIFT_ASSIGN);

				return Token(Location(file, start_pos, 2), TOKEN_LSHIFT);

			case '=': // <=
				return Token(Location(file, start_pos, 2), TOKEN_LESS_OR_EQUAL);

			default: // <
				return Token(Location(file, start_pos, 1), TOKEN_LESS_THAN);
		}
	}

	static Token get_rangbrack_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '>': // >>
				if (file[start_pos + 2] == '=') // >>=
					return Token(Location(file, start_pos, 3), TOKEN_RSHIFT_ASSIGN);

				return Token(Location(file, start_pos, 2), TOKEN_RSHIFT);

			case '=': // <=
				return Token(Location(file, start_pos, 2), TOKEN_GREATER_OR_EQUAL);

			default: // >
				return Token(Location(file, start_pos, 1), TOKEN_GREATER_THAN);
		}
	}

	static Token get_ampersand_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos])
		{
			case '=':
				return Token(Location(file, start_pos, 2), TOKEN_BITAND_ASSIGN);

			case '&':
				return Token(Location(file, start_pos, 2), TOKEN_BOOLEAN_AND);

			default:
				return Token(Location(file, start_pos, 1), TOKEN_AMPERSAND);
		}
	}
	
	static Token get_pipeline_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '=':
				return Token(Location(file, start_pos, 2), TOKEN_BITOR_ASSIGN);

			case '|':
				return Token(Location(file, start_pos, 2), TOKEN_BOOLEAN_OR);

			default:
				return Token(Location(file, start_pos, 1), TOKEN_PIPELINE);
		}
	}

	static Token get_carrot_operator(const File& file, const usize start_pos)
	{
		if (file[start_pos + 1] == '=')
			return Token(Location(file, start_pos, 2), TOKEN_BITXOR_ASSIGN);

		return Token(Location(file, start_pos, 1), TOKEN_CARROT);
	}

	static Token get_equals_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '=':
				return Token(Location(file, start_pos, 2), TOKEN_EQUALS);

			case '>':
				return Token(Location(file, start_pos, 2), TOKEN_DOUBLE_ARROW);

			default:
				return Token(Location(file, start_pos, 1), TOKEN_ASSIGN);
		}
	}

	static Token get_exclamation_operator(const File& file, const usize start_pos)
	{
		if (file[start_pos + 1] == '=')
			return Token(Location(file, start_pos, 2), TOKEN_NOT_EQUALS);

		return Token(Location(file, start_pos, 1), TOKEN_BOOLEAN_NOT);
	}

	static Token get_question_operator(const File& file, const usize start_pos)
	{
		if (file[start_pos + 1] == '?')		
			return Token(Location(file, start_pos, 2), TOKEN_OPTION);
	
		return Token(Location(file, start_pos, 1), TOKEN_QUESTION);
	}

	static Token get_modulus_operator(const File& file, const usize start_pos)
	{
		if (file[start_pos + 1] == '=')
			return Token(Location(file, start_pos, 2), TOKEN_MODULUS_ASSIGN);
		
		return Token(Location(file, start_pos, 1), TOKEN_MODULUS);
	}

	static Token get_colon_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case ':':
				return Token(Location(file, start_pos, 2), TOKEN_SCOPE);

			case '=':
				return Token(Location(file, start_pos, 2), TOKEN_BECOME_ASSIGN);

			default:
				return Token(Location(file, start_pos, 1), TOKEN_COLON);
		}
	}

	static Result<Token> get_operator_token(const File& file, const usize start_pos)
	{
		switch (file[start_pos])
		{
			case '+': // +, ++, +=
				return get_plus_operator(file, start_pos);

			case '-': // -, --, -=, ->
				return get_hyphen_operator(file, start_pos);

			case '*': // *, **, *=
				return get_asterisk_operator(file, start_pos);

			case '/': // /, /=
				return get_slash_operator(file, start_pos);

			case '<': // <, <<, <=
				return get_langbrack_operator(file, start_pos);

			case '>': // >, >>, >=
				return get_rangbrack_operator(file, start_pos);

			case '&': // &, &=
				return get_ampersand_operator(file, start_pos);

			case '|': // |, |=
				return get_pipeline_operator(file, start_pos);

			case '^': // ^, ^=
				return get_carrot_operator(file, start_pos);

			case '=': // =, ==, =>
				return get_equals_operator(file, start_pos);

			case '!': // !, !=
				return get_exclamation_operator(file, start_pos);

			case '?': // ?, ??
				return get_question_operator(file, start_pos);				

			case '%': // %, %=
				return get_modulus_operator(file, start_pos);

			case ':': // :, ::
				return get_colon_operator(file, start_pos);

			default:
				throw std::runtime_error("invalid chracter given in operator: '" + String(1, file[0]) + "'");
		}
	}

	static Result<Token> get_quote_token(const source::File& file, const usize start_pos)
	{
		char terminal_character = file[start_pos];
		auto pos = start_pos + 1;

		while (true)
		{
			auto current_character = file[pos]; 

			if (current_character == '\0')
			{
				print_error(file.get_snippet(start_pos, pos - start_pos), "unterminated string literal");
				return {};
			}

			if (current_character == terminal_character && file[pos - 1] != '\\')
				break;

			pos += 1;
		}

		auto type = terminal_character == '\''
			? TOKEN_CHAR_LITERAL
			: TOKEN_STRING_LITERAL;
			
		return Token(Location(file, start_pos, pos - start_pos), type);
	}

	static Result<Token> get_next_token(const source::File& file, const usize start_pos)
	{
		auto type = get_char_type(file[start_pos]);

		switch (type)
		{
			case CHAR_NULL:
				break;

			case CHAR_IDENTIFIER:
				return get_identifier_token(file, start_pos);

			case CHAR_SEPARATOR:
				return get_separator_token(file, start_pos);

			case CHAR_DOT:
				return get_dot_token(file, start_pos);

			case CHAR_DIGIT:
				return get_digit_token(file, start_pos);

			case CHAR_OPERATOR:
				return get_operator_token(file, start_pos);

			case CHAR_QUOTE:
				return get_quote_token(file, start_pos);

			case CHAR_INVALID:
				print_error(file.get_snippet(start_pos, 1), "invalid character in source file '" + String(1, file[start_pos]) + "'");
				return {};
		}

		return Token(Location(file, start_pos, 1), TOKEN_END_OF_FILE);
	}

	Result<Array<Token>> tokenize(const source::File& file)
	{	
		Array<Token> out;

		out.reserve(10);

		usize position = 0;

		do
		{
			position = find_next_position(file, position);

			if (out.size() == out.capacity())
				out.reserve(out.size() * 2);

			auto res = get_next_token(file, position);

			if (!res)
				return {};

			out.emplace_back(res.unwrap());
			position += out.back().location().length();
		}
		while (out.back().type() != TOKEN_END_OF_FILE);

		return out;
	}
}
