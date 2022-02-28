#include <warbler/lexicon/tokenizer.hpp>

// local headers
#include <warbler/util/print.hpp>

// standard headers
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <unordered_map>

#define MAX_KeywordLENGTH	(15)

namespace warbler::lexicon
{
	using source::File;
	using source::Location;

	enum class CharType
	{
		Invalid,
		Null,
		Identifier,
		Separator,
		Dot,
		Digit,
		Operator,
		Quote
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
					return TokenType::KeywordBreak;
				break;

			case 'c':
				if (text[1] == 'a')
				{
					if (match_str(text + 2, "se"))
						return TokenType::KeywordCase;
				}
				else if (text[1] == 'o')
				{
					if (match_str(text + 2, "ntinue"))
						return TokenType::KeywordContinue;
				}
				break;

			case 'e':
				switch (text[1])
				{
					case 'l':
						if (match_str(text + 2, "se"))
							return TokenType::KeywordElse;
						break;

					case 'n':
						if (match_str(text + 2, "um"))
							return TokenType::KeywordEnum;
						break;

					case 'x':
						if (match_str(text + 2, "port"))
							return TokenType::KeywordExport;
						break;

					default:
						return TokenType::Identifier;
				}
				break;

			case 'f':
				switch (text[1])
				{
					case 'a':
						if (match_str(text + 2, "lse"))
							return TokenType::KeywordFalse;
						break;
						
					case 'o':
						if (text[2] == 'r' && text[3] == '\0')
							return TokenType::KeywordFor;
						break;

					case 'u':
						if (match_str(text + 2, "nction"))
							return TokenType::KeywordFunction;
						break;

					default:
						return TokenType::Identifier;
				}
				break;

			case 'i':
				if (text[1] == 'f')
				{
					if (text[2] == '\0')
						return TokenType::KeywordIf;
				}
				else if (text[1] == 'm')
				{
					if (match_str(text + 2, "port"))
						return TokenType::KeywordImport;
				}
				break;

			case 'l':
				if (match_str(text + 1, "oop"))
					return TokenType::KeywordLoop;
				break;

			case 'm':
				if (text[1] == 'a')
				{
					if (match_str(text + 2, "tch"))
						return TokenType::KeywordMatch;
				}
				else if (text[1] == 'u')
				{
					if (match_str(text + 2, "t"))
						return TokenType::KeywordMut;
				}
				break;

			case 'p':
				if (text[1] == 'r')
				{
					if (match_str(text + 2, "ivate"))
						return TokenType::KeywordPrivate;
				}
				else if (text[1] == 'u')
				{
					if (match_str(text + 2, "blic"))
						return TokenType::KeywordPublic;
				}
				break;

			case 'r':
				if (match_str(text + 1, "eturn"))
					return TokenType::KeywordReturn;
				break;

			case 's':
				if (match_str(text + 1, "truct"))
					return TokenType::KeywordStruct;
				break;

			case 't':
				switch (text[1])
				{
					case 'h':
						if (match_str(text + 2, "en"))
							return TokenType::KeywordThen;
						break;

					case 'r':
						if (match_str(text + 2, "ue"))
							return TokenType::KeywordTrue;
						break;

					case 'y':
						if (match_str(text + 2, "pe"))
							return TokenType::KeywordType;
						break;
				}
				break;

			case 'u':
				if (match_str(text + 1, "nion"))
					return TokenType::KeywordUnion;
				break;

			case 'v':
				if (match_str(text + 1, "ar"))
					return TokenType::KeywordVar;
				break;

			case 'w':
				if (match_str(text + 1, "hile"))
					return TokenType::KeywordWhile;
				break;
				
			default:
				break;
		}

		return TokenType::Identifier;
	}
	


	void init_char_types()
	{
		char_types[0] = CharType::Null;

		// setting up identifier characters
		char_types[(usize)'_'] = CharType::Identifier;
		for (usize i = 'a'; i <= 'z'; ++i)
			char_types[i] = CharType::Identifier;
		for (usize i = 'A'; i <= 'Z'; ++i)
			char_types[i] = CharType::Identifier;
		for (usize i = '0'; i <= '9'; ++i)
			char_types[i] = CharType::Digit;

		// setting up separator characters
		char_types[(size_t)'('] = CharType::Separator;
		char_types[(size_t)')'] = CharType::Separator;
		char_types[(size_t)'['] = CharType::Separator;
		char_types[(size_t)']'] = CharType::Separator;
		char_types[(size_t)'{'] = CharType::Separator;
		char_types[(size_t)'}'] = CharType::Separator;
		char_types[(size_t)';'] = CharType::Separator;
		char_types[(size_t)','] = CharType::Separator;

		// dot character
		char_types[(size_t)'.'] = CharType::Dot;

		// setting up operator characters
		char_types[(size_t)'!'] = CharType::Operator;
		char_types[(size_t)'%'] = CharType::Operator;
		char_types[(size_t)'^'] = CharType::Operator;
		char_types[(size_t)'&'] = CharType::Operator;
		char_types[(size_t)'*'] = CharType::Operator;
		char_types[(size_t)'-'] = CharType::Operator;
		char_types[(size_t)'='] = CharType::Operator;
		char_types[(size_t)'|'] = CharType::Operator;
		char_types[(size_t)'+'] = CharType::Operator;
		char_types[(size_t)'<'] = CharType::Operator;
		char_types[(size_t)'>'] = CharType::Operator;
		char_types[(size_t)'?'] = CharType::Operator;
		char_types[(size_t)'/'] = CharType::Operator;
		char_types[(size_t)':'] = CharType::Operator;

		// setting literal types
		char_types[(size_t)'\''] = CharType::Quote;
		char_types[(size_t)'\"'] = CharType::Quote;
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

		return type == CharType::Identifier || type == CharType::Digit;
	}

	static Token get_identifier_token(const File& file, const usize start_pos)
	{
		auto pos = start_pos + 1;

		while (is_char_alphanumeric(file[pos]))
			pos += 1;

		usize length = pos - start_pos;

		return Token(Location(file, start_pos, length), TokenType::Identifier);
	}

	static Token get_separator_token(const File& file, const usize start_pos)
	{
		TokenType type;

		switch (file[start_pos])
		{
			case '(':
				type = TokenType::LeftParenthesis;
				break;

			case ')':
				type = TokenType::RightParenthesis;
				break;

			case '[':
				type = TokenType::LeftBracket;
				break;

			case ']':
				type = TokenType::RightBracket;
				break;

			case '{':
				type = TokenType::LeftBrace;
				break;

			case '}':
				type = TokenType::RightBrace;
				break;

			case ',':
				type = TokenType::Comma;
				break;

			case ';':
				type = TokenType::Semicolon;
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

			if (type == CharType::Dot)
			{
				decimal_count += 1;
			}
			else if (type != CharType::Digit)
			{
				break;
			}

			pos += 1;
		}

		auto length = pos - start_pos;

		if (decimal_count > 1)
		{
			print_error(source::Snippet(file, start_pos, length), "only one decimal is allowed in float literal");
			return {};
		}

		auto type = decimal_count > 0
			? TokenType::FloatLiteral
			: TokenType::IntegerLiteral;

		return Token(Location(file, start_pos, length), type);
	}

	static Result<Token> get_dot_token(const File& file, const usize start_pos)
	{
		if (get_char_type(file[start_pos + 1]) == CharType::Digit)
			return get_digit_token(file, start_pos);

		usize pos = start_pos + 1;

		while (get_char_type(file[pos]) == CharType::Dot)
			pos += 1;

		auto length = pos - start_pos;

		TokenType type;

		switch (length)
		{
			case 1:
				type = TokenType::Dot;
				break;

			case 3:
				type = TokenType::Elipsis;
				break;

			default:
			{
				auto text = source::Snippet(file, start_pos, length);
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
				return Token(Location(file, start_pos, 2), TokenType::AddAssign);

			default:
				return Token(Location(file, start_pos, 1), TokenType::Plus);
		}
	}

	static Token get_hyphen_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '=': // -=
				return Token(Location(file, start_pos, 2), TokenType::SubtractAssign);

			case '>': // ->
				return Token(Location(file, start_pos, 2), TokenType::SingleArrow);

			default: // -
				return Token(Location(file, start_pos, 1), TokenType::Minus);
		}
	}

	static Token get_asterisk_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '*': // **
				return Token(Location(file, start_pos, 2), TokenType::Pow);

			case '=': // *=
				return Token(Location(file, start_pos, 2), TokenType::MultiplyAssign);

			default: // *
				return Token(Location(file, start_pos, 1), TokenType::Asterisk);
		}
	}

	static Token get_slash_operator(const File& file, const usize start_pos)
	{
		return file[start_pos + 1] == '='
			? Token(Location(file, start_pos, 2), TokenType::DivideAssign)
			: Token(Location(file, start_pos, 1), TokenType::Slash);
	}

	static Token get_langbrack_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '<': // <<
				if (file[start_pos + 2] == '=') // <<=
					return Token(Location(file, start_pos, 3), TokenType::LeftBitShiftAssign);

				return Token(Location(file, start_pos, 2), TokenType::LeftBitShift);

			case '=': // <=
				return Token(Location(file, start_pos, 2), TokenType::LessThanOrEqualTo);

			default: // <
				return Token(Location(file, start_pos, 1), TokenType::LessThan);
		}
	}

	static Token get_rangbrack_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '>': // >>
				if (file[start_pos + 2] == '=') // >>=
					return Token(Location(file, start_pos, 3), TokenType::RightBitShiftAssign);

				return Token(Location(file, start_pos, 2), TokenType::RightBitShift);

			case '=': // <=
				return Token(Location(file, start_pos, 2), TokenType::GreaterThanOrEqualTo);

			default: // >
				return Token(Location(file, start_pos, 1), TokenType::GreaterThan);
		}
	}

	static Token get_ampersand_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos])
		{
			case '=':
				return Token(Location(file, start_pos, 2), TokenType::BitwiseAndAssign);

			case '&':
				return Token(Location(file, start_pos, 2), TokenType::BooleanAnd);

			default:
				return Token(Location(file, start_pos, 1), TokenType::Ampersand);
		}
	}
	
	static Token get_pipeline_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '=':
				return Token(Location(file, start_pos, 2), TokenType::BitwiseOrAssign);

			case '|':
				return Token(Location(file, start_pos, 2), TokenType::BooleanOr);

			default:
				return Token(Location(file, start_pos, 1), TokenType::Pipeline);
		}
	}

	static Token get_carrot_operator(const File& file, const usize start_pos)
	{
		return file[start_pos + 1] == '='
			? Token(Location(file, start_pos, 2), TokenType::BitwiseXorAssign)
			: Token(Location(file, start_pos, 1), TokenType::Carrot);
	}

	static Token get_equals_operator(const File& file, const usize start_pos)
	{
		switch (file[start_pos + 1])
		{
			case '=':
				return Token(Location(file, start_pos, 2), TokenType::Equals);

			case '>':
				return Token(Location(file, start_pos, 2), TokenType::DoubleArrow);

			default:
				return Token(Location(file, start_pos, 1), TokenType::Assign);
		}
	}

	static Token get_exclamation_operator(const File& file, const usize start_pos)
	{
		return file[start_pos + 1] == '='
			? Token(Location(file, start_pos, 2), TokenType::NotEquals)
			: Token(Location(file, start_pos, 1), TokenType::BooleanNot);
	}

	static Token get_question_operator(const File& file, const usize start_pos)
	{
		return file[start_pos + 1] == '?'
			? Token(Location(file, start_pos, 2), TokenType::Option)
			: Token(Location(file, start_pos, 1), TokenType::Question);
	}

	static Token get_modulus_operator(const File& file, const usize start_pos)
	{
		return file[start_pos + 1] == '='
			? Token(Location(file, start_pos, 2), TokenType::ModulusAssign)
			: Token(Location(file, start_pos, 1), TokenType::Modulus);
	}

	static Token get_colon_operator(const File& file, const usize start_pos)
	{
		return file[start_pos + 1] == ':'
			? Token(Location(file, start_pos, 2), TokenType::Scope)
			: Token(Location(file, start_pos, 1), TokenType::Colon);
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
				print_error(source::Snippet(file, start_pos, pos - start_pos), "unterminated string literal");
				return {};
			}

			if (current_character == terminal_character && file[pos - 1] != '\\')
				break;

			pos += 1;
		}

		auto type = terminal_character == '\''
			? TokenType::CharLiteral
			: TokenType::StringLiteral;
			
		return Token(Location(file, start_pos, pos - start_pos), type);
	}

	static Result<Token> get_next_token(const source::File& file, const usize start_pos)
	{
		auto type = get_char_type(file[start_pos]);

		switch (type)
		{
			case CharType::Null:
				break;

			case CharType::Identifier:
				return get_identifier_token(file, start_pos);

			case CharType::Separator:
				return get_separator_token(file, start_pos);

			case CharType::Dot:
				return get_dot_token(file, start_pos);

			case CharType::Digit:
				return get_digit_token(file, start_pos);

			case CharType::Operator:
				return get_operator_token(file, start_pos);

			case CharType::Quote:
				return get_quote_token(file, start_pos);

			case CharType::Invalid:
				print_error(source::Snippet(file, start_pos, 1), "invalid character in source file '" + String(1, file[start_pos]) + "'");
				return {};
		}

		return Token(Location(file, start_pos, 1), TokenType::EndOfFile);
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
		while (out.back().type() != TokenType::EndOfFile);

		return out;
	}
}
