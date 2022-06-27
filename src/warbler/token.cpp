#include <warbler/token.hpp>

#include <warbler/util/print.hpp>
#include <cstring>

namespace warbler
{
	Token::Token(const File& file, usize pos, usize length, TokenType type) :
	_file(file),
	_pos(pos),
	_length(length),
	_type(type)
	{}

	static usize get_next_pos(const File& file, usize pos)
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

	static inline bool is_identifier_char(char c)
	{
		switch (c)
		{
			case '_':
			case 'a': case 'A':
			case 'b': case 'B':
			case 'c': case 'C':
			case 'd': case 'D':
			case 'e': case 'E':
			case 'f': case 'F':
			case 'g': case 'G':
			case 'h': case 'H':
			case 'i': case 'I':
			case 'j': case 'J':
			case 'k': case 'K':
			case 'l': case 'L':
			case 'm': case 'M':
			case 'n': case 'N':
			case 'o': case 'O':
			case 'p': case 'P':
			case 'q': case 'Q':
			case 'r': case 'R':
			case 's': case 'S':
			case 't': case 'T':
			case 'u': case 'U':
			case 'v': case 'V':
			case 'w': case 'W':
			case 'x': case 'X':
			case 'y': case 'Y':
			case 'z': case 'Z':
				return true;

			default:
				return false;
		}
	}

	static inline bool is_digit_char(char c)
	{
		switch (c)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return true;

			default:
				return false;
		}
	}

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

					default:
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

	static Token get_quote_token(const File& file, const usize start_pos)
	{
		char terminal_character = file[start_pos];
		auto pos = start_pos + 1;

		while (true)
		{
			auto current_character = file[pos]; 

			if (current_character == '\0' || (current_character == terminal_character && file[pos - 1] != '\\'))
				break;

			pos += 1;
		}

		auto type = terminal_character == '\''
			? TokenType::CharLiteral
			: TokenType::StringLiteral;
			
		return Token(file, start_pos, pos - start_pos, type);
	}

	static Token get_identifier_token(const File& file, const usize start_pos)
	{
		auto pos = start_pos + 1;

		while (is_identifier_char(file[pos]) || is_digit_char(file[pos]))
			pos += 1;

		auto length = pos - start_pos;
		
		static char tmp_key[2048];

		strncpy(tmp_key, &file.src()[start_pos], length);
		tmp_key[length] = '\0';

		auto type = get_identifier_type(tmp_key);

		return Token(file, start_pos, length, type);
	}

	static Token get_digit_token(const File& file, const usize start_pos)
	{
		auto pos = start_pos;
		bool is_float = false;

		while (true)
		{
			char c = file[pos];

			if (!is_digit_char(c))
			{
				if (c != '.')
				{
					break;
				}

				is_float = true;
			}

			pos += 1;
		}

		auto length = pos - start_pos;

		auto type = is_float
			? TokenType::FloatLiteral
			: TokenType::IntegerLiteral;

		return Token(file, start_pos, length, type);
	}

	static Token get_next_token(const File& file, usize start_pos)
	{
		switch (file[start_pos])
		{
			case '\0':
				return Token(file, start_pos, 0, TokenType::EndOfFile);

			case '_':
			case 'a': case 'A':
			case 'b': case 'B':
			case 'c': case 'C':
			case 'd': case 'D':
			case 'e': case 'E':
			case 'f': case 'F':
			case 'g': case 'G':
			case 'h': case 'H':
			case 'i': case 'I':
			case 'j': case 'J':
			case 'k': case 'K':
			case 'l': case 'L':
			case 'm': case 'M':
			case 'n': case 'N':
			case 'o': case 'O':
			case 'p': case 'P':
			case 'q': case 'Q':
			case 'r': case 'R':
			case 's': case 'S':
			case 't': case 'T':
			case 'u': case 'U':
			case 'v': case 'V':
			case 'w': case 'W':
			case 'x': case 'X':
			case 'y': case 'Y':
			case 'z': case 'Z':
				return get_identifier_token(file, start_pos);

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return get_digit_token(file, start_pos);
			
			// Separators
			case '(':
				return Token(file, start_pos, 1, TokenType::LeftParenthesis);

			case ')':
				return Token(file, start_pos, 1, TokenType::RightParenthesis);

			case '[':
				return Token(file, start_pos, 1, TokenType::LeftBracket);

			case ']':
				return Token(file, start_pos, 1, TokenType::RightBracket);

			case '{':
				return Token(file, start_pos, 1, TokenType::LeftBrace);

			case '}':
				return Token(file, start_pos, 1, TokenType::RightBrace);

			case ',':
				return Token(file, start_pos, 1, TokenType::Comma);

			case ';':
				return Token(file, start_pos, 1, TokenType::Semicolon);

			case ':':
				if (file[start_pos + 1] == ':')
				{
					return Token(file, start_pos, 1, TokenType::Semicolon);
				}
				return Token(file, start_pos, 1, TokenType::Colon);

			case '.':
				switch (file[start_pos + 1])
				{
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						return get_digit_token(file, start_pos);

					case '.':
						if (file[start_pos + 2] == '.')
						{
							return Token(file, start_pos, 3, TokenType::Elipsis);
						}
						return Token(file, start_pos, 2, TokenType::Range);
					
					default:
						return Token(file, start_pos, 1, TokenType::Dot);
				}

			// Operators
			case '<':
				if (file[start_pos + 1] == '<')
				{
					if (file[start_pos + 2] == '=')
					{
						return Token(file, start_pos, 3, TokenType::LeftBitShiftAssign);
					}
					return Token(file, start_pos, 2, TokenType::LeftBitShift);
				}
				else if (file[start_pos + 1] == '=')
				{
					return Token(file, start_pos, 2, TokenType::LessThanOrEqualTo);
				}
				return Token(file, start_pos, 1, TokenType::LessThan);

			case '>':
				if (file[start_pos + 1] == '>')
				{
					if (file[start_pos + 2] == '=')
					{
						return Token(file, start_pos, 3, TokenType::RightBitShiftAssign);
					}
					return Token(file, start_pos, 2, TokenType::RightBitShift);
				}
				else if (file[start_pos + 1] == '=')
				{
					return Token(file, start_pos, 2, TokenType::GreaterThanOrEqualTo);
				}
				return Token(file, start_pos, 1, TokenType::GreaterThan);

			case '%':
				return file[start_pos + 1] == '='
					? Token(file, start_pos, 2, TokenType::ModulusAssign)
					: Token(file, start_pos, 1, TokenType::Modulus);

			case '^':
				return file[start_pos + 1] == '='
					? Token(file, start_pos, 2, TokenType::BitwiseXorAssign)
					: Token(file, start_pos, 1, TokenType::BitwiseXor);
				
			case '&':
				if (file[start_pos + 1] == '&')
				{
					if (file[start_pos + 2] == '=')
					{
						return Token(file, start_pos, 3, TokenType::BooleanAndAssign);
					}
					return Token(file, start_pos, 2, TokenType::BooleanAnd);
				}
				else if (file[start_pos + 1] == '=')
				{
					return Token(file, start_pos, 2, TokenType::BitwiseAndAssign);
				}
				return Token(file, start_pos, 1, TokenType::Ampersand);

			case '*':
				return file[start_pos + 1] == '='
					? Token(file, start_pos, 2, TokenType::MultiplyAssign)
					: Token(file, start_pos, 1, TokenType::Asterisk);

			case '-':
				if (file[start_pos + 1] == '=')
				{
					return Token(file, start_pos, 2, TokenType::SubtractAssign);
				}
				else if (file[start_pos + 1] == '>')
				{
					return Token(file, start_pos, 2, TokenType::SingleArrow);
				}
				return Token(file, start_pos, 1, TokenType::Minus);

			case '=':
				if (file[start_pos + 1] == '=')
				{
					return Token(file, start_pos, 2, TokenType::Equals);
				}
				else if (file[start_pos + 1] == '>')
				{
					return Token(file, start_pos, 2, TokenType::DoubleArrow);
				}
				return Token(file, start_pos, 1, TokenType::Assign);

			case '|':
				if (file[start_pos + 1] == '|')
				{
					if (file[start_pos + 2] == '=')
					{
						return Token(file, start_pos, 3, TokenType::BooleanOrAssign);
					}
					return Token(file, start_pos, 2, TokenType::BooleanOr);
				}
				else if (file[start_pos + 1] == '=')
				{
					return Token(file, start_pos, 2, TokenType::BitwiseOrAssign);
				}
				return Token(file, start_pos, 1, TokenType::Pipeline);

			case '+':
				return file[start_pos + 1] == '='
					? Token(file, start_pos, 2, TokenType::AddAssign)
					: Token(file, start_pos, 1, TokenType::Plus);

			case '?':
				return Token(file, start_pos, 1, TokenType::Question);

			case '!':
				return file[start_pos + 1] == '='
					? Token(file, start_pos, 2, TokenType::NotEquals)
					: Token(file, start_pos, 1, TokenType::BooleanNot);

			case '/':
				return file[start_pos + 1] == '='
					? Token(file, start_pos, 2, TokenType::DivideAssign)
					: Token(file, start_pos, 1, TokenType::Slash);

			case '\'':
			case '\"':
				return get_quote_token(file, start_pos);

			default:
				print_error(Snippet(file, start_pos, 1), "An invalid character was found in the text file: '" + file.get_text(start_pos, 1) + "'.");
				abort();
		}
	}

	void Token::increment()
	{
		auto next_token_pos = get_next_pos(_file, _pos + _length);
		auto next_token = get_next_token(_file, next_token_pos);

		new (this) auto(next_token);
	}

	Token Token::get_initial(const File& file)
	{
		auto pos = get_next_pos(file, 0);

		return get_next_token(file, pos);
	}

	const char *Token::category() const 
	{
		switch (_type)
		{
			case TokenType::EndOfFile:
				return "end-of-file";

			case TokenType::Identifier:
				return "symbol";

			case TokenType::LeftParenthesis:
			case TokenType::RightParenthesis:
			case TokenType::LeftBracket:
			case TokenType::RightBracket:
			case TokenType::LeftBrace:
			case TokenType::RightBrace:
			case TokenType::Semicolon:
			case TokenType::Colon:
			case TokenType::Comma:
				return "separator";

			case TokenType::Dot:
			case TokenType::Range:
			case TokenType::Elipsis:
			case TokenType::Ampersand:
			case TokenType::Pipeline:
			case TokenType::Carrot:
			case TokenType::LeftBitShift:
			case TokenType::RightBitShift:
			case TokenType::BooleanNot:
			case TokenType::BooleanAnd:
			case TokenType::BooleanOr:
			case TokenType::BitwiseNot:
			case TokenType::BitwiseXor:
			case TokenType::Equals:
			case TokenType::NotEquals:
			case TokenType::LessThanOrEqualTo:
			case TokenType::GreaterThanOrEqualTo:
			case TokenType::LessThan:
			case TokenType::GreaterThan:
			case TokenType::SingleArrow:
			case TokenType::DoubleArrow:
			case TokenType::Option:
			case TokenType::Question:
			case TokenType::Assign:
			case TokenType::AddAssign:
			case TokenType::SubtractAssign:
			case TokenType::MultiplyAssign:
			case TokenType::DivideAssign:
			case TokenType::ModulusAssign:
			case TokenType::LeftBitShiftAssign:
			case TokenType::RightBitShiftAssign:
			case TokenType::BitwiseAndAssign:
			case TokenType::BitwiseOrAssign:
			case TokenType::BitwiseXorAssign:
			case TokenType::BooleanOrAssign:
			case TokenType::BooleanAndAssign:
			case TokenType::Modulus:
			case TokenType::Slash:
			case TokenType::Asterisk:
			case TokenType::Plus:
			case TokenType::Minus:
			case TokenType::Scope:
				return "operator";

			case TokenType::IntegerLiteral:
				return "integer literal";
			case TokenType::FloatLiteral:
				return "float literal";
			case TokenType::HexadecimalLiteral:
				return "hexadecimal literal";
			case TokenType::BinaryLiteral:
				return "binary literal";
			case TokenType::OctalLiteral:
				return "octal literal";
			case TokenType::CharLiteral:
				return "character literal";
			case TokenType::StringLiteral:
				return "string literal";

			case TokenType::KeywordBreak:
			case TokenType::KeywordCase:
			case TokenType::KeywordContinue:
			case TokenType::KeywordElse:
			case TokenType::KeywordEnum:
			case TokenType::KeywordExport:
			case TokenType::KeywordFalse:
			case TokenType::KeywordFor:
			case TokenType::KeywordFunction:
			case TokenType::KeywordIf:
			case TokenType::KeywordImport:
			case TokenType::KeywordLoop:
			case TokenType::KeywordMatch:
			case TokenType::KeywordMut:
			case TokenType::KeywordPrivate:
			case TokenType::KeywordPublic:
			case TokenType::KeywordReturn:
			case TokenType::KeywordStruct:
			case TokenType::KeywordThen:
			case TokenType::KeywordTrue:
			case TokenType::KeywordType:
			case TokenType::KeywordUnion:
			case TokenType::KeywordVar:
			case TokenType::KeywordWhile:
				return "keyword";

			default:
				throw std::runtime_error("Invalid type");
		}
	}

	Token::operator String() const
	{
		if (_type == TokenType::EndOfFile)
		{
			return category();
		}
		
		return String(category()) + " '" + text() + '\'';
	}

	bool Token::operator==(const String& text) const
	{
		if (text.size() != _length)
			return false;

		for (usize i = 0; i < _length; ++i)
		{
			if (_file[_pos + i] != text[i])
				return false;
		}

		return true;
	}
}
