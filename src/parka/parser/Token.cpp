#include "parka/parser/Token.hpp"
#include "parka/log/Log.hpp"

#include <cstring>

namespace parka
{
	Token::Token(const File& file, usize index, usize length, TokenType type):
	_snippet(file, index, length),
	_type(type)
	{}

	Token& Token::operator=(Token&& other)
	{
		_snippet = std::move(other._snippet);
		_type = other._type;

		return *this;
	}

	Token& Token::operator=(const Token& other)
	{
		_snippet = other._snippet;
		_type = other._type;

		return *this;
	}

	static usize getEndOfLinePos(const File& file, usize pos)
	{
		for (usize i = pos; i < file.length(); ++i)
		{
			if (file[i] == '\n')
				return i + 1;
		}

		return file.length();
	}

	static usize getEndOfBlockCommentPos(const File& file, usize pos)
	{
		for (usize i = pos; i < file.length(); ++i)
		{
			if (file[i] == '*' && file[i + 1] == '/')
				return i + 2;
		}

		return file.length();
	}

	static usize getNextPos(const File& file, usize pos)
	{
		for (usize i = pos; i < file.length(); ++i)
		{
			auto c = file[i];

			if (c <= ' ')
				continue;

			if (c == '/')
			{
				switch (file[i + 1])
				{
					case '/': // Line comment
						i = getEndOfLinePos(file, i + 2) - 1;
						continue;

					case '*': // Block comment
						i = getEndOfBlockCommentPos(file, i + 2) - 1;
						continue;

					default:
						break;
				}
			}

			return i;
		}

		return file.length();
	}

	inline bool isIdentifierChar(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
	}

	inline bool isDigitChar(char c)
	{
		return (c >= '0' && c <= '9');
	}

	TokenType getQuoteType(char terminal)
	{
		switch (terminal)
		{
			case '\'':
				return TokenType::CharacterLiteral;

			case '\"':
				return TokenType::StringLiteral;

			default:
				log::fatal("Invalid quote type: $", terminal);
		}
	}

	Token getQuoteToken(const File& file, const usize startPos)
	{
		auto terminal = file[startPos];
		auto type = getQuoteType(terminal);
		usize length = 1;
		auto isEscaped = false;

		for (usize i = startPos + length; file[i] != terminal || isEscaped; ++i)
		{
			char c = file[i];

			if (!c)
			{
				auto token = Token(file, startPos, length, TokenType::EndOfFile);

				log::error(token, "$ is unterminated.", type);
				
				return token;
			}

			if (c == '\\')
			{
				isEscaped = !isEscaped;
				continue;
			}
			
			length += 1;
		}
		
		length += 1;

		auto token = Token(file, startPos, length, type);

		return token;
	}

	Token getIdentifierToken(const File& file, const usize startPos)
	{
		usize i = startPos + 1;

		while (true)
		{
			char c = file[i];

			if (!isIdentifierChar(c) && !isDigitChar(c))
				break;

			i += 1;
		}

		auto length = i - startPos;

		return Token(file, startPos, length, TokenType::Identifier);
	}

	Token getDigitToken(const File& file, const usize startPos)
	{
		auto isFloat = false;
		usize length = 0;

		for (usize i = startPos; ; ++i)
		{
			char c = file[i];

			if (isDigitChar(c))
				continue;

			if (c != '.' || isFloat)
			{
				length = i - startPos;
				break;
			}
				
			isFloat = true;
		}

		auto type = isFloat
			? TokenType::FloatLiteral
			: TokenType::IntegerLiteral;
		auto token = Token(file, startPos, length, type);

		return token;
	}

	Token getNextToken(const File& file, usize startPos)
	{
		char c = file[startPos];

		switch (c)
		{
			case '\0':
				return Token(file, startPos, 0, TokenType::EndOfFile);

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
				return getIdentifierToken(file, startPos);

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
				return getDigitToken(file, startPos);
			
			// Separators
			case '(':
				return Token(file, startPos, 1, TokenType::LeftParenthesis);

			case ')':
				return Token(file, startPos, 1, TokenType::RightParenthesis);

			case '[':
				return Token(file, startPos, 1, TokenType::LeftBracket);

			case ']':
				return Token(file, startPos, 1, TokenType::RightBracket);

			case '{':
				return Token(file, startPos, 1, TokenType::LeftBrace);

			case '}':
				return Token(file, startPos, 1, TokenType::RightBrace);

			case ',':
				return Token(file, startPos, 1, TokenType::Comma);

			case ';':
				return Token(file, startPos, 1, TokenType::Semicolon);

			case ':':
				return file[startPos + 1] == ':'
					? Token(file, startPos, 1, TokenType::Semicolon)
					: Token { file, startPos, 1, TokenType::Colon };

			case '.':
			{
				char c1 = file[startPos + 1];

				if (isDigitChar(c1))
				{
					return getDigitToken(file, startPos);
				}
				else if (c1 == '.')
				{
					return file[startPos + 2] == '.'
						? Token(file, startPos, 3, TokenType::Elipsis)
						: Token(file, startPos, 2, TokenType::Range);
				}
				
				return Token(file, startPos, 1, TokenType::Dot);
			}

			// Operators
			case '<':
				if (file[startPos + 1] == '<')
				{
					return file[startPos + 2] == '='
						? Token(file, startPos, 3, TokenType::LeftBitShiftAssign)
						: Token(file, startPos, 2, TokenType::LeftBitShift);
				}
				else if (file[startPos + 1] == '=')
				{
					return Token(file, startPos, 2, TokenType::LessThanOrEqualTo);
				}

				return Token(file, startPos, 1, TokenType::LessThan);

			case '>':
				if (file[startPos + 1] == '>')
				{
					return file[startPos + 2] == '='
						? Token(file, startPos, 3, TokenType::RightBitShiftAssign)
						: Token(file, startPos, 2, TokenType::RightBitShift);
				}
				else if (file[startPos + 1] == '=')
				{
					return Token(file, startPos, 2, TokenType::GreaterThanOrEqualTo);
				}

				return Token(file, startPos, 1, TokenType::GreaterThan);

			case '$':
				return file[startPos + 1] == '='
					? Token(file, startPos, 2, TokenType::ModulusAssign)
					: Token(file, startPos, 1, TokenType::Modulus);

			case '^':
				return file[startPos + 1] == '='
					? Token(file, startPos, 2, TokenType::BitwiseXorAssign)
					: Token(file, startPos, 1, TokenType::BitwiseXor);
				
			case '&':
				if (file[startPos + 1] == '&')
				{
					return file[startPos + 2] == '='
						? Token(file, startPos, 3, TokenType::BooleanAndAssign)
						: Token(file, startPos, 2, TokenType::BooleanAnd);
				}
				else if (file[startPos + 1] == '=')
				{
					return Token(file, startPos, 2, TokenType::BitwiseAndAssign);
				}

				return Token(file, startPos, 1, TokenType::Ampersand);

			case '*':
				return file[startPos + 1] == '='
					? Token(file, startPos, 2, TokenType::MultiplyAssign)
					: Token(file, startPos, 1, TokenType::Asterisk);

			case '-':
				if (file[startPos + 1] == '=')
				{
					return Token(file, startPos, 2, TokenType::SubtractAssign);
				}
				else if (file[startPos + 1] == '>')
				{
					return Token(file, startPos, 2, TokenType::SingleArrow);
				}

				return Token(file, startPos, 1, TokenType::Minus);

			case '=':
				if (file[startPos + 1] == '=')
				{
					return Token(file, startPos, 2, TokenType::Equals);
				}
				else if (file[startPos + 1] == '>')
				{
					return Token(file, startPos, 2, TokenType::DoubleArrow);
				}

				return Token(file, startPos, 1, TokenType::Assign);

			case '|':
				if (file[startPos + 1] == '|')
				{
					return file[startPos + 2] == '='
						? Token(file, startPos, 3, TokenType::BooleanOrAssign)
						: Token(file, startPos, 2, TokenType::BooleanOr);
				}
				else if (file[startPos + 1] == '=')
				{
					return Token(file, startPos, 2, TokenType::BitwiseOrAssign);
				}
				
				return Token(file, startPos, 1, TokenType::Pipe);

			case '+':
				return file[startPos + 1] == '='
					? Token(file, startPos, 2, TokenType::AddAssign)
					: Token(file, startPos, 1, TokenType::Plus);

			case '?':
				return Token(file, startPos, 1, TokenType::Question);

			case '!':
				return file[startPos + 1] == '='
					? Token(file, startPos, 2, TokenType::NotEquals)
					: Token(file, startPos, 1, TokenType::BooleanNot);

			case '/':
				return file[startPos + 1] == '='
					? Token(file, startPos, 2, TokenType::DivideAssign)
					: Token(file, startPos, 1, TokenType::Slash);

			case '\'':
			case '\"':
				return getQuoteToken(file, startPos);

			default:
				break;
		}

		// TODO: Rethink handling of strange characters
		auto token = Token(file, startPos, 1, TokenType::EndOfFile);

		log::error(token, "An invalid character was found in the source file.");

		return token;
	}

	void Token::increment()
	{
		usize nextTokenPos = getNextPos(_snippet.file(), _snippet.index() + _snippet.length());

		*this = getNextToken(_snippet.file(), nextTokenPos);
	}

	Token Token::initial(const File& file)
	{
		auto pos = getNextPos(file, 0);
		auto token = getNextToken(file, pos);

		return token;
	}

	String Token::text() const
	{
		return _snippet.text();
	}

	String Token::category() const
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
			case TokenType::Pipe:
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
			case TokenType::CharacterLiteral:
				return "character literal";
			case TokenType::StringLiteral:
				return "string literal";

			default:
				log::fatal("Invalid TokenType: $", _type);
		}
	}

	// bool Token::operator ==(const String& text) const
	// {
	// 	if (_length != text.length())
	// 		return false;

	// 	return !strncmp(_position.ptr(), text.c_str(), _length);
	// }

	std::ostream& operator<<(std::ostream& out, TokenType type)
	{
		switch (type)
		{
			case TokenType::EndOfFile:
				out << "end of file";
				break;
				
			case TokenType::Invalid:
				out << "invalid token";
				break;
				
			case TokenType::Identifier:
				out << "identifier";
				break;
				
			case TokenType::LeftParenthesis:
				out << "(";
				break;
				
			case TokenType::RightParenthesis:
				out << ")";
				break;
				
			case TokenType::LeftBracket:
				out << "[";
				break;
				
			case TokenType::RightBracket:
				out << "]";
				break;
				
			case TokenType::LeftBrace:
				out << "{";
				break;
				
			case TokenType::RightBrace:
				out << "}";
				break;
				
			case TokenType::Semicolon:
				out << ";";
				break;
				
			case TokenType::Colon:
				out << ":";
				break;
				
			case TokenType::Comma:
				out << ",";
				break;
				
			case TokenType::Dot:
				out << ".";
				break;
				
			case TokenType::Range:
				out << "";
				break;
				
			case TokenType::Elipsis:
				out << ".";
				break;
				
			case TokenType::Ampersand:
				out << "&";
				break;
				
			case TokenType::Pipe:
				out << "|";
				break;
				
			case TokenType::Carrot:
				out << "^";
				break;
				
			case TokenType::LeftBitShift:
				out << "<<";
				break;
				
			case TokenType::RightBitShift:
				out << ">>";
				break;
				
			case TokenType::BooleanNot:
				out << "not";
				break;
				
			case TokenType::BooleanAnd:
				out << "and";
				break;
				
			case TokenType::BooleanOr:
				out << "or";
				break;
				
			case TokenType::BitwiseNot:
				out << "~";
				break;
				
			case TokenType::BitwiseXor:
				out << "^";
				break;
				
			case TokenType::Equals:
				out << "==";
				break;
				
			case TokenType::NotEquals:
				out << "!=";
				break;
				
			case TokenType::LessThanOrEqualTo:
				out << "<=";
				break;
				
			case TokenType::GreaterThanOrEqualTo:
				out << ">=";
				break;
				
			case TokenType::LessThan:
				out << "<";
				break;
				
			case TokenType::GreaterThan:
				out << ">";
				break;
				
			case TokenType::SingleArrow:
				out << "->";
				break;
				
			case TokenType::DoubleArrow:
				out << "=>";
				break;
				
			case TokenType::Option:
				out << "??";
				break;
				
			case TokenType::Question:
				out << "?";
				break;
				
			case TokenType::Assign:
				out << "=";
				break;
				
			case TokenType::AddAssign:
				out << "+=";
				break;
				
			case TokenType::SubtractAssign:
				out << "-=";
				break;
				
			case TokenType::MultiplyAssign:
				out << "*=";
				break;
				
			case TokenType::DivideAssign:
				out << "/=";
				break;
				
			case TokenType::ModulusAssign:
				out << "$=";
				break;
				
			case TokenType::LeftBitShiftAssign:
				out << "<<=";
				break;
				
			case TokenType::RightBitShiftAssign:
				out << ">>=";
				break;
				
			case TokenType::BitwiseAndAssign:
				out << "&=";
				break;
				
			case TokenType::BitwiseOrAssign:
				out << "|=";
				break;
				
			case TokenType::BitwiseXorAssign:
				out << "^=";
				break;
				
			case TokenType::BooleanOrAssign:
				out << "||=";
				break;
				
			case TokenType::BooleanAndAssign:
				out << "&&=";
				break;
				
			case TokenType::Modulus:
				out << "$";
				break;
				
			case TokenType::Slash:
				out << "/";
				break;
				
			case TokenType::Asterisk:
				out << "*";
				break;
				
			case TokenType::Plus:
				out << "+";
				break;
				
			case TokenType::Minus:
				out << "-";
				break;
				
			case TokenType::Scope:
				out << "::";
				break;
				
			case TokenType::IntegerLiteral:
				out << "{integer}";
				break;
				
			case TokenType::FloatLiteral:
				out << "{float}";
				break;
				
			case TokenType::CharacterLiteral:
				out << "{char}";
				break;
				
			case TokenType::StringLiteral:
				out << "{string}";
				break;
				

			default:
				out << '(' << (int)type << ") Invalid";
		}

		return out;
	}

	std::ostream& operator<<(std::ostream& out, const Token& token)
	{
		out << token._type << " `" << token._snippet << "`";

		return out;
	}
}
