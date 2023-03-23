#include "parka/token.hpp"

#include "parka/util/print.hpp"
#include <string.h>

usize getEndOfLinePos(const char *src, usize pos)
{
	while (true)
	{
		char c = src[pos];

		if (c == '\0')
			break;

		if (c == '\n')
		{
			pos += 1;
			break;
		}

		pos += 1;
	}

	return pos;
}

usize getEndOfBlockCommentPos(const char *src, usize pos)
{
	while (true)
	{
		char c = src[pos];

		if (c == '\0')
			break;

		if (c == '*' && src[pos + 1] == '/')
		{
			pos += 2;
			break;
		}

		pos += 1;
	}

	return pos;
}

usize getNextPos(const char *src, usize pos)
{
	while (true)
	{
		char c = src[pos];

		if (c == '\0')
			break;

		if (c == '/')
		{
			switch (src[pos + 1])
			{
				case '/': // Line comment
					pos = getEndOfLinePos(src, pos + 2);
					continue;

				case '*': // Block comment
					pos = getEndOfBlockCommentPos(src, pos + 2);
					continue;

				default:
					return pos;
			}
		}

		if (c > ' ')
			break;

		pos += 1;
	}

	return pos;
}

inline bool isIdentifierChar(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
	// switch (c)
	// {
	// 	case '_':
	// 	case 'a': case 'A':
	// 	case 'b': case 'B':
	// 	case 'c': case 'C':
	// 	case 'd': case 'D':
	// 	case 'e': case 'E':
	// 	case 'f': case 'F':
	// 	case 'g': case 'G':
	// 	case 'h': case 'H':
	// 	case 'i': case 'I':
	// 	case 'j': case 'J':
	// 	case 'k': case 'K':
	// 	case 'l': case 'L':
	// 	case 'm': case 'M':
	// 	case 'n': case 'N':
	// 	case 'o': case 'O':
	// 	case 'p': case 'P':
	// 	case 'q': case 'Q':
	// 	case 'r': case 'R':
	// 	case 's': case 'S':
	// 	case 't': case 'T':
	// 	case 'u': case 'U':
	// 	case 'v': case 'V':
	// 	case 'w': case 'W':
	// 	case 'x': case 'X':
	// 	case 'y': case 'Y':
	// 	case 'z': case 'Z':
	// 		return true;

	// 	default:
	// 		return false;
	// }
}

inline bool isDigitChar(char c)
{
	return (c >= '0' && c <= '9');
	// switch (c)
	// {
	// 	case '0':
	// 	case '1':
	// 	case '2':
	// 	case '3':
	// 	case '4':
	// 	case '5':
	// 	case '6':
	// 	case '7':
	// 	case '8':
	// 	case '9':
	// 		return true;

	// 	default:
	// 		return false;
	// }
}

TokenType getIdentifierType(const char *text)
{
	switch (text[0])
	{
		case 'b':
			if (!strcmp(text + 1, "reak"))
				return TokenType::KeywordBreak;
			break;

		case 'c':
			if (text[1] == 'a')
			{
				if (!strcmp(text + 2, "se"))
					return TokenType::KeywordCase;
			}
			else if (text[1] == 'o')
			{
				if (!strcmp(text + 2, "ntinue"))
					return TokenType::KeywordContinue;
			}
			break;

		case 'e':
			switch (text[1])
			{
				case 'l':
					if (!strcmp(text + 2, "se"))
						return TokenType::KeywordElse;
					break;

				case 'n':
					if (!strcmp(text + 2, "um"))
						return TokenType::KeywordEnum;
					break;

				case 'x':
					if (!strcmp(text + 2, "port"))
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
					if (!strcmp(text + 2, "lse"))
						return TokenType::KeywordFalse;
					break;
					
				case 'o':
					if (text[2] == 'r' && text[3] == '\0')
						return TokenType::KeywordFor;
					break;

				case 'u':
					if (!strcmp(text + 2, "nction"))
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
				if (!strcmp(text + 2, "port"))
					return TokenType::KeywordImport;
			}
			break;

		case 'l':
			if (!strcmp(text + 1, "oop"))
				return TokenType::KeywordLoop;
			break;

		case 'm':
			if (text[1] == 'a')
			{
				if (!strcmp(text + 2, "tch"))
					return TokenType::KeywordMatch;
			}
			else if (text[1] == 'u')
			{
				if (!strcmp(text + 2, "t"))
					return TokenType::KeywordMut;
			}
			break;

		case 'p':
			if (text[1] == 'r')
			{
				if (!strcmp(text + 2, "ivate"))
					return TokenType::KeywordPrivate;
			}
			else if (text[1] == 'u')
			{
				if (!strcmp(text + 2, "blic"))
					return TokenType::KeywordPublic;
			}
			break;

		case 'r':
			if (!strcmp(text + 1, "eturn"))
				return TokenType::KeywordReturn;
			break;

		case 's':
			if (!strcmp(text + 1, "truct"))
				return TokenType::KeywordStruct;
			break;

		case 't':
			switch (text[1])
			{
				case 'h':
					if (!strcmp(text + 2, "en"))
						return TokenType::KeywordThen;
					break;

				case 'r':
					if (!strcmp(text + 2, "ue"))
						return TokenType::KeywordTrue;
					break;

				case 'y':
					if (!strcmp(text + 2, "pe"))
						return TokenType::KeywordType;
					break;

				default:
					break;
			}
			break;

		case 'u':
			if (!strcmp(text + 1, "nion"))
				return TokenType::KeywordUnion;
			break;

		case 'v':
			if (!strcmp(text + 1, "ar"))
				return TokenType::KeywordVar;
			break;

		case 'w':
			if (!strcmp(text + 1, "hile"))
				return TokenType::KeywordWhile;
			break;
			
		default:
			break;
	}

	return TokenType::Identifier;
}

Token getQuoteToken(const File *file, const usize startPos)
{
	char terminal = fileGetChar(file, startPos);
	TokenType type = terminal == '\''
		? TokenType::CharacterLiteral
		: TokenType::StringLiteral;

	Token token =
	{
		.file = file,
		.pos = startPos,
		.type = type,
		.length = 1
	};

	bool isEscaped = false;

	while (true)
	{
		char c = file->src[token.pos + token.length]; 

		// TODO: This should be an error
		if (!c)
		{
			const char *typeName = terminal == '\''
				? "Character"
				: "String";

			printTokenError(&token, "%s literal is unterminated.", typeName);
			token.type = TokenType::EndOfFile;
			break;
		}

		if (c == '\\')
		{
			isEscaped = !isEscaped;
			continue;
		}
		
		token.length += 1;

		if (c == terminal && !isEscaped)
			break;
	}
	
	return token;
}

Token getIdentifierToken(const File& file, const usize startPos)
{
	usize pos = startPos + 1;

	while (isIdentifierChar(file->src[pos]) || isDigitChar(file->src[pos]))
		pos += 1;

	usize length = pos - startPos;
	
	// TODO: Make sure okay size
	char tmpKey[512];

	strncpy(tmpKey, file->src + startPos, length);
	tmpKey[length] = '\0';

	TokenType type = getIdentifierType(tmpKey);

	return Token(file, startPos, length, type);
}

Token getDigitToken(const File *file, const usize startPos)
{
	usize pos = startPos;
	bool isFloat = false;

	while (true)
	{
		char c = fileGetChar(file, pos);

		if (!isDigitChar(c))
		{
			if (c != '.')
			{
				break;
			}

			isFloat = true;
		}

		pos += 1;
	}

	usize length = pos - startPos;

	TokenType type = isFloat
		? TokenType::FloatLiteral
		: TokenType::IntegerLiteral;

	return Token(file, startPos, length, type);
}

Token getNextToken(const File *file, usize startPos)
{
	char c = fileGetChar(file, startPos);

	switch (c)
	{
		case '\0':
			return (Token) { file, startPos, 0, TokenType::EndOfFile };

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
			return (Token) { file, startPos, 1, TokenType::LeftParenthesis };

		case ')':
			return (Token) { file, startPos, 1, TokenType::RightParenthesis };

		case '[':
			return (Token) { file, startPos, 1, TokenType::LeftBracket };

		case ']':
			return (Token) { file, startPos, 1, TokenType::RightBracket };

		case '{':
			return (Token) { file, startPos, 1, TokenType::LeftBrace };

		case '}':
			return (Token) { file, startPos, 1, TokenType::RightBrace };

		case ',':
			return (Token) { file, startPos, 1, TokenType::Comma };

		case ';':
			return (Token) { file, startPos, 1, TokenType::Semicolon };

		case ':':
			return fileGetChar(file, startPos + 1) == ':'
				? Token(file, startPos, 1, TokenType::Semicolon)
				: Token { file, startPos, 1, TokenType::Colon };

		case '.':
		{
			char c1 = fileGetChar(file, startPos + 1);

			if (isDigitChar(c1))
			{
				return getDigitToken(file, startPos);
			}
			else if (c1 == '.')
			{
				return fileGetChar(file, startPos + 2) == '.'
					? (Token) { file, startPos, 3, TokenType::Elipsis }
					: (Token) { file, startPos, 2, TokenType::Range };
			}
			
			return (Token) { file, startPos, 1, TokenType::Dot };
		}

		// Operators
		case '<':
			if (fileGetChar(file, startPos + 1) == '<')
			{
				return fileGetChar(file, startPos + 2) == '='
					? (Token) { file, startPos, 3, TokenType::LeftBitShiftAssign }
					: (Token) { file, startPos, 2, TokenType::LeftBitShift };
			}
			else if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TokenType::LessThanOrEqualTo };
			}

			return (Token) { file, startPos, 1, TokenType::LessThan };

		case '>':
			if (fileGetChar(file, startPos + 1) == '>')
			{
				return fileGetChar(file, startPos + 2) == '='
					? (Token) { file, startPos, 3, TokenType::RightBitShiftAssign }
					: (Token) { file, startPos, 2, TokenType::RightBitShift };
			}
			else if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TokenType::GreaterThanOrEqualTo };
			}

			return (Token) { file, startPos, 1, TokenType::GreaterThan };

		case '%':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TokenType::ModulusAssign }
				: (Token) { file, startPos, 1, TokenType::Modulus };

		case '^':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TokenType::BitwiseXorAssign }
				: (Token) { file, startPos, 1, TokenType::BitwiseXor };
			
		case '&':
			if (fileGetChar(file, startPos + 1) == '&')
			{
				return fileGetChar(file, startPos + 2) == '='
					? (Token) { file, startPos, 3, TokenType::BooleanAndAssign }
					: (Token) { file, startPos, 2, TokenType::BooleanAnd };
			}
			else if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TokenType::BitwiseAndAssign };
			}

			return (Token) { file, startPos, 1, TokenType::Ampersand };

		case '*':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TokenType::MultiplyAssign }
				: (Token) { file, startPos, 1, TokenType::Asterisk };

		case '-':
			if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TokenType::SubtractAssign };
			}
			else if (fileGetChar(file, startPos + 1) == '>')
			{
				return (Token) { file, startPos, 2, TokenType::SingleArrow };
			}

			return (Token) { file, startPos, 1, TokenType::Minus };

		case '=':
			if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TokenType::Equals };
			}
			else if (fileGetChar(file, startPos + 1) == '>')
			{
				return (Token) { file, startPos, 2, TokenType::DoubleArrow };
			}

			return (Token) { file, startPos, 1, TokenType::Assign };

		case '|':
			if (fileGetChar(file, startPos + 1) == '|')
			{
				return fileGetChar(file, startPos + 2) == '='
					? (Token) { file, startPos, 3, TokenType::BooleanOrAssign }
					: (Token) { file, startPos, 2, TokenType::BooleanOr };
			}
			else if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TokenType::BitwiseOrAssign };
			}
			
			return (Token) { file, startPos, 1, TokenType::Pipe };

		case '+':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TokenType::AddAssign }
				: (Token) { file, startPos, 1, TokenType::Plus };

		case '?':
			return (Token) { file, startPos, 1, TokenType::Question };

		case '!':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TokenType::NotEquals }
				: (Token) { file, startPos, 1, TokenType::BooleanNot };

		case '/':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TokenType::DivideAssign }
				: (Token) { file, startPos, 1, TokenType::Slash };

		case '\'':
		case '\"':
			return getQuoteToken(file, startPos);

		default:
			break;
	}

	Token token =
	{
		.file = file,
		.pos = startPos,
		.length = 1,
		.type = TokenType::EndOfFile
	};

	printTokenError(&token, "An invalid character was found in the source file");

	return token;
}

void Token::increment()
{
	usize nextTokenPos = getNextPos(token.file()->src, token.pos() + token.length());

	new (this) auto(getNextToken(token.file(), nextTokenPos));
}

Token getInitialToken(const File *file)
{
	usize pos = getNextPos(file->src, 0);

	return getNextToken(file, pos);
}

String Token::category() const
{
	switch (token.type())
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
			exitWithErrorFmt("Invalid TokenType: %d", token.type());
	}
}

char operator[](usize index) const
{
	return fileGetChar(_file, index);
}

String Token::text() const
{
	return fileGetText(_file, _pos, _length);
}

bool Token::operator==(const Token& other) const
{
	if (&_file != &other.file() || _length != other.length() || _type != other.type())
		return false;

	if (_pos == b.pos())
		return true;

	for (usize i = 0; i < length; ++i)
	{
		if (fileGetChar(file, _pos + i) != fileGetChar(file, b.pos() + i))
			return false;
	}

	return true;
}
