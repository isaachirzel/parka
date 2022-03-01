#include <warbler/lexicon/token.hpp>

#include <warbler/util/print.hpp>

namespace warbler::lexicon
{
	using source::File;
	using source::Snippet;

	Token::Token(const source::File& file, usize pos, usize length, TokenType type) :
	_file(file),
	_pos(pos),
	_length(length),
	_type(type)
	{}

	usize Token::get_next_pos()
	{
		usize next_pos = _pos + _length;

		while (true)
		{
			auto character = _file[next_pos];

			if (character == '\0' || character > ' ')
				break;

			next_pos += 1;
		}

		return next_pos;
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

	static Token get_quote_token(const source::File& file, const usize start_pos)
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

		while (is_identifier_char(file[pos]))
			pos += 1;

		auto length = pos - start_pos;

		return Token(file, start_pos, length, TokenType::Identifier);
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
				print_error(Snippet(file, start_pos, 1), "invalid character in text file: '" + file.get_text(start_pos, 1) + "'");
				abort();
		}
	}

	Token& Token::next()
	{
		auto next_token_pos = get_next_pos();
		auto next_token = get_next_token(_file, next_token_pos);

		new (this) auto(next_token);
		return *this;
	}
}
