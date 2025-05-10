#include "parka/parser/Token.hpp"
#include "parka/enum/KeywordType.hpp"
#include "parka/fs/FilePosition.hpp"
#include "parka/fs/FileSnippet.hpp"
#include "parka/log/Log.hpp"

#include <cstring>

namespace parka
{
	Token::Token(const fs::FileSnippet& snippet, TokenType type):
		_snippet(snippet),
		_type(type)
	{}

	inline bool isIdentifierChar(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
	}

	inline bool isDigitChar(char c)
	{
		return (c >= '0' && c <= '9');
	}

	TokenType getUnterminatedQuoteType(char terminal)
	{
		switch (terminal)
		{
			case '\'':
				return TokenType::UnterminatedCharacterLiteral;

			case '\"':
				return TokenType::UnterminatedStringLiteral;

			default:
				break;
		}

		abort();
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
				break;
		}

		abort();	
	}

	Token getQuoteToken(const fs::FilePosition& startPos)
	{
		auto terminal = *startPos;
		auto type = getQuoteType(terminal);
		usize length = 1;
		auto isEscaped = false;

		while (true)
		{
			char c = startPos[length];

			if (c == terminal || isEscaped)
				break;

			if (!c)
			{
				auto unterminatedType = getUnterminatedQuoteType(terminal);
				auto token = Token(fs::FileSnippet(startPos, length), unterminatedType);

				log::unterminatedQuoteTokenError(token);
				
				// TODO: Solution
				// auto solutionSnippet = token.snippet().sub(token.snippet().length() - 1, 1);

				// log::solution(solutionSnippet, "Terminate the string with a `\"` after this character.");
				
				return token;
			}

			if (c == '\\')
				isEscaped = !isEscaped;
			
			length += 1;
		}
		
		length += 1;

		auto token = Token(fs::FileSnippet(startPos, length), type);

		return token;
	}

	Token getIdentifierToken(const fs::FilePosition& startPos)
	{
		usize length = 1;

		while (true)
		{
			char c = startPos[length];

			if (!isIdentifierChar(c) && !isDigitChar(c))
				break;

			length += 1;
		}

		return Token(fs::FileSnippet(startPos, length), TokenType::Identifier);
	}

	Token getDigitToken(const fs::FilePosition& position)
	{
		auto isFloat = false;
		auto length = (u32)0;

		while(true)
		{
			auto c = position[length];

			if (!isDigitChar(c))
			{
				if (c != '.')
					break;

				if (isFloat)
					break;

				auto next = position[length + 1];

				if (!isDigitChar(next))
					break;

				isFloat = true;
				length += 1;
			}

			length += 1;
		}

		auto type = isFloat
			? TokenType::FloatLiteral
			: TokenType::IntegerLiteral;
		auto token = Token(fs::FileSnippet(position, length), type);

		return token;
	}

	Token getNextToken(const fs::FilePosition& startPos)
	{
		char c = *startPos;

		switch (c)
		{
			case '\0':
				return Token(fs::FileSnippet(startPos, 0), TokenType::EndOfFile);

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
				return getIdentifierToken(startPos);

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
				return getDigitToken(startPos);
			
			// Separators
			case '(':
				return Token(fs::FileSnippet(startPos, 1), TokenType::LeftParenthesis);

			case ')':
				return Token(fs::FileSnippet(startPos, 1), TokenType::RightParenthesis);

			case '[':
				return Token(fs::FileSnippet(startPos, 1), TokenType::LeftBracket);

			case ']':
				return Token(fs::FileSnippet(startPos, 1), TokenType::RightBracket);

			case '{':
				return Token(fs::FileSnippet(startPos, 1), TokenType::LeftBrace);

			case '}':
				return Token(fs::FileSnippet(startPos, 1), TokenType::RightBrace);

			case ',':
				return Token(fs::FileSnippet(startPos, 1), TokenType::Comma);

			case ';':
				return Token(fs::FileSnippet(startPos, 1), TokenType::Semicolon);

			case ':':
				return startPos[1] == ':'
					? Token(fs::FileSnippet(startPos, 2), TokenType::Scope)
					: Token(fs::FileSnippet(startPos, 1), TokenType::Colon);

			case '.':
			{
				char c1 = startPos[1];

				if (isDigitChar(c1))
				{
					return getDigitToken(startPos);
				}
				else if (c1 == '.')
				{
					return startPos[2] == '.'
						? Token(fs::FileSnippet(startPos, 3), TokenType::Elipsis)
						: Token(fs::FileSnippet(startPos, 2), TokenType::Range);
				}
				
				return Token(fs::FileSnippet(startPos, 1), TokenType::Dot);
			}

			// Operators
			case '<':
				if (startPos[1] == '<')
				{
					return startPos[2] == '='
						? Token(fs::FileSnippet(startPos, 3), TokenType::LeftBitShiftAssign)
						: Token(fs::FileSnippet(startPos, 2), TokenType::LeftBitShift);
				}
				else if (startPos[1] == '=')
				{
					return Token(fs::FileSnippet(startPos, 2), TokenType::LessThanOrEqualTo);
				}

				return Token(fs::FileSnippet(startPos, 1), TokenType::LessThan);

			case '>':
				if (startPos[1] == '>')
				{
					return startPos[2] == '='
						? Token(fs::FileSnippet(startPos, 3), TokenType::RightBitShiftAssign)
						: Token(fs::FileSnippet(startPos, 2), TokenType::RightBitShift);
				}
				else if (startPos[1] == '=')
				{
					return Token(fs::FileSnippet(startPos, 2), TokenType::GreaterThanOrEqualTo);
				}

				return Token(fs::FileSnippet(startPos, 1), TokenType::GreaterThan);

			case '$':
				return startPos[1] == '='
					? Token(fs::FileSnippet(startPos, 2), TokenType::ModulusAssign)
					: Token(fs::FileSnippet(startPos, 1), TokenType::Modulus);

			case '^':
				return startPos[1] == '='
					? Token(fs::FileSnippet(startPos, 2), TokenType::BitwiseXorAssign)
					: Token(fs::FileSnippet(startPos, 1), TokenType::BitwiseXor);
				
			case '&':
				if (startPos[1] == '&')
				{
					return startPos[2] == '='
						? Token(fs::FileSnippet(startPos, 3), TokenType::BooleanAndAssign)
						: Token(fs::FileSnippet(startPos, 2), TokenType::BooleanAnd);
				}
				else if (startPos[1] == '=')
				{
					return Token(fs::FileSnippet(startPos, 2), TokenType::BitwiseAndAssign);
				}

				return Token(fs::FileSnippet(startPos, 1), TokenType::Ampersand);

			case '*':
				return startPos[1] == '='
					? Token(fs::FileSnippet(startPos, 2), TokenType::MultiplyAssign)
					: Token(fs::FileSnippet(startPos, 1), TokenType::Asterisk);

			case '-':
				if (startPos[1] == '=')
				{
					return Token(fs::FileSnippet(startPos, 2), TokenType::SubtractAssign);
				}
				else if (startPos[1] == '>')
				{
					return Token(fs::FileSnippet(startPos, 2), TokenType::SingleArrow);
				}

				return Token(fs::FileSnippet(startPos, 1), TokenType::Minus);

			case '=':
				if (startPos[1] == '=')
				{
					return Token(fs::FileSnippet(startPos, 2), TokenType::Equals);
				}
				else if (startPos[1] == '>')
				{
					return Token(fs::FileSnippet(startPos, 2), TokenType::DoubleArrow);
				}

				return Token(fs::FileSnippet(startPos, 1), TokenType::Assign);

			case '|':
				if (startPos[1] == '|')
				{
					return startPos[2] == '='
						? Token(fs::FileSnippet(startPos, 3), TokenType::BooleanOrAssign)
						: Token(fs::FileSnippet(startPos, 2), TokenType::BooleanOr);
				}
				else if (startPos[1] == '=')
				{
					return Token(fs::FileSnippet(startPos, 2), TokenType::BitwiseOrAssign);
				}
				
				return Token(fs::FileSnippet(startPos, 1), TokenType::Pipe);

			case '+':
				return startPos[1] == '='
					? Token(fs::FileSnippet(startPos, 2), TokenType::AddAssign)
					: Token(fs::FileSnippet(startPos, 1), TokenType::Plus);

			case '?':
				return Token(fs::FileSnippet(startPos, 1), TokenType::Question);

			case '!':
				return startPos[1] == '='
					? Token(fs::FileSnippet(startPos, 2), TokenType::NotEquals)
					: Token(fs::FileSnippet(startPos, 1), TokenType::BooleanNot);

			case '/':
				return startPos[1] == '='
					? Token(fs::FileSnippet(startPos, 2), TokenType::DivideAssign)
					: Token(fs::FileSnippet(startPos, 1), TokenType::Slash);

			case '%':
				return startPos[1] == '='
					? Token(fs::FileSnippet(startPos, 2), TokenType::ModulusAssign)
					: Token(fs::FileSnippet(startPos, 1), TokenType::Modulus);

			case '\'':
			case '\"':
				return getQuoteToken(startPos);

			default:
				break;
		}

		// TODO: Rethink handling of strange characters
		auto token = Token(fs::FileSnippet(startPos, 1), TokenType::EndOfFile);

		log::invalidTokenError(token);

		return token;
	}

	void Token::increment()
	{
		auto start = _snippet.position();
		auto position = fs::FilePosition(start.file(), start.index() + _snippet.length(), start.line(), start.column() + _snippet.length());

		position.seekNext();

		*this = getNextToken(position);
	}

	Token Token::initial(const fs::File& file)
	{
		auto position = fs::FilePosition(file, 0, 1, 1);

		position.seekNext();

		auto token = getNextToken(position);

		return token;
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
				return "(invalid category)";
		}
	}

	KeywordType Token::getKeywordType() const
	{
		return toKeywordType(_snippet.ptr(), _snippet.length());
	}

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
				out << "integer";
				break;
				
			case TokenType::FloatLiteral:
				out << "float";
				break;
				
			case TokenType::CharacterLiteral:
				out << "char";
				break;
				
			case TokenType::StringLiteral:
				out << "string";
				break;
				
			case TokenType::UnterminatedStringLiteral:
				out << "unterminated string";
				break;

			default:
				out << "(" << (int)type << ") Invalid";
		}

		return out;
	}

	std::ostream& operator<<(std::ostream& out, const Token& token)
	{
		out << token._type << " `" << token._snippet << "`";

		return out;
	}
}
