#include <warbler/token.h>

#include <warbler/util/print.h>
#include <string.h>

static usize getNextPos(const File *file, usize pos)
{
	while (true)
	{
		char character = file->src[pos];

		if (character == '\0' || character > ' ')
			break;

		pos += 1;
	}

	return pos;
}

static inline bool isIdentifierChar(char c)
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

static inline bool isDigitChar(char c)
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

static inline bool MatchStr(const char * const text, const char * const compare, const usize size)
{
	for (usize i = 0; i < size; ++i)
	{
		if (text[i] != compare[i])
			return false;
	}

	return true;
}

#define matchStr(text, compare) MatchStr(text, compare, sizeof(compare))

TokenType getIdentifierType(const char *text)
{
	switch (text[0])
	{
		case 'b':
			if (matchStr(text + 1, "reak"))
				return TOKEN_KEYWORD_BREAK;
			break;

		case 'c':
			if (text[1] == 'a')
			{
				if (matchStr(text + 2, "se"))
					return TOKEN_KEYWORD_CASE;
			}
			else if (text[1] == 'o')
			{
				if (matchStr(text + 2, "ntinue"))
					return TOKEN_KEYWORD_CONTINUE;
			}
			break;

		case 'e':
			switch (text[1])
			{
				case 'l':
					if (matchStr(text + 2, "se"))
						return TOKEN_KEYWORD_ELSE;
					break;

				case 'n':
					if (matchStr(text + 2, "um"))
						return TOKEN_KEYWORD_ENUM;
					break;

				case 'x':
					if (matchStr(text + 2, "port"))
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
					if (matchStr(text + 2, "lse"))
						return TOKEN_KEYWORD_FALSE;
					break;
					
				case 'o':
					if (text[2] == 'r'  *text[3] == '\0')
						return TOKEN_KEYWORD_FOR;
					break;

				case 'u':
					if (matchStr(text + 2, "nction"))
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
				if (matchStr(text + 2, "port"))
					return TOKEN_KEYWORD_IMPORT;
			}
			break;

		case 'l':
			if (matchStr(text + 1, "oop"))
				return TOKEN_KEYWORD_LOOP;
			break;

		case 'm':
			if (text[1] == 'a')
			{
				if (matchStr(text + 2, "tch"))
					return TOKEN_KEYWORD_MATCH;
			}
			else if (text[1] == 'u')
			{
				if (matchStr(text + 2, "t"))
					return TOKEN_KEYWORD_MUT;
			}
			break;

		case 'p':
			if (text[1] == 'r')
			{
				if (matchStr(text + 2, "ivate"))
					return TOKEN_KEYWORD_PRIVATE;
			}
			else if (text[1] == 'u')
			{
				if (matchStr(text + 2, "blic"))
					return TOKEN_KEYWORD_PUBLIC;
			}
			break;

		case 'r':
			if (matchStr(text + 1, "eturn"))
				return TOKEN_KEYWORD_RETURN;
			break;

		case 's':
			if (matchStr(text + 1, "truct"))
				return TOKEN_KEYWORD_STRUCT;
			break;

		case 't':
			switch (text[1])
			{
				case 'h':
					if (matchStr(text + 2, "en"))
						return TOKEN_KEYWORD_THEN;
					break;

				case 'r':
					if (matchStr(text + 2, "ue"))
						return TOKEN_KEYWORD_TRUE;
					break;

				case 'y':
					if (matchStr(text + 2, "pe"))
						return TOKEN_KEYWORD_TYPE;
					break;

				default:
					break;
			}
			break;

		case 'u':
			if (matchStr(text + 1, "nion"))
				return TOKEN_KEYWORD_UNION;
			break;

		case 'v':
			if (matchStr(text + 1, "ar"))
				return TOKEN_KEYWORD_VAR;
			break;

		case 'w':
			if (matchStr(text + 1, "hile"))
				return TOKEN_KEYWORD_WHILE;
			break;
			
		default:
			break;
	}

	return TOKEN_IDENTIFIER;
}

static Token getQuoteToken(const File *file, const usize startPos)
{
	char terminalCharacter = fileGetChar(file, startPos);
	usize pos = startPos + 1;

	while (true)
	{
		char currentCharacter = file->src[pos]; 

		if (currentCharacter == '\0' || (currentCharacter == terminalCharacter && file->src[pos - 1] != '\\'))
			break;

		pos += 1;
	}

	TokenType type = terminalCharacter == '\''
		? TOKEN_CHARACTER_LITERAL
		: TOKEN_STRING_LITERAL;
		
	return (Token) { file, startPos, pos - startPos, type };
}

static Token getIdentifierToken(const File *file, const usize startPos)
{
	usize pos = startPos + 1;

	while (isIdentifierChar(file->src[pos]) || isDigitChar(file->src[pos]))
		pos += 1;

	usize length = pos - startPos;
	
	// TODO: Make sure okay size
	static char tmpKey[512];

	strncpy(tmpKey, file->src + startPos, length);
	tmpKey[length] = '\0';

	TokenType type = getIdentifierType(tmpKey);

	return (Token) { file, startPos, length, type };
}

static Token getDigitToken(const File *file, const usize startPos)
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
		? TOKEN_FLOAT_LITERAL
		: TOKEN_INTEGER_LITERAL;

	return (Token) { file, startPos, length, type };
}

static Token getNextToken(const File *file, usize startPos)
{
	switch (fileGetChar(file, startPos))
	{
		case '\0':
			return (Token) { file, startPos, 0, TOKEN_END_OF_FILE };

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
			return (Token) { file, startPos, 1, TOKEN_LEFT_PARENTHESIS };

		case ')':
			return (Token) { file, startPos, 1, TOKEN_RIGHT_PARENTHESIS };

		case '[':
			return (Token) { file, startPos, 1, TOKEN_LEFT_BRACKET };

		case ']':
			return (Token) { file, startPos, 1, TOKEN_RIGHT_BRACKET };

		case '{':
			return (Token) { file, startPos, 1, TOKEN_LEFT_BRACE };

		case '}':
			return (Token) { file, startPos, 1, TOKEN_RIGHT_BRACE };

		case ',':
			return (Token) { file, startPos, 1, TOKEN_COMMA };

		case ';':
			return (Token) { file, startPos, 1, TOKEN_SEMICOLON };

		case ':':
			if (fileGetChar(file, startPos + 1) == ':')
			{
				return (Token) { file, startPos, 1, TOKEN_SEMICOLON };
			}
			
			return (Token) { file, startPos, 1, TOKEN_COLON };

		case '.':
			switch (fileGetChar(file, startPos + 1))
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
					return getDigitToken(file, startPos);

				case '.':
					if (fileGetChar(file, startPos + 2) == '.')
					{
						return (Token) { file, startPos, 3, TOKEN_ELIPSIS };
					}
					return (Token) { file, startPos, 2, TOKEN_RANGE };
				
				default:
					return (Token) { file, startPos, 1, TOKEN_DOT };
			}

		// Operators
		case '<':
			if (fileGetChar(file, startPos + 1) == '<')
			{
				if (fileGetChar(file, startPos + 2) == '=')
				{
					return (Token) { file, startPos, 3, TOKEN_LEFT_BIT_SHIFT_ASSIGN };
				}
				return (Token) { file, startPos, 2, TOKEN_LEFT_BIT_SHIFT };
			}
			else if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TOKEN_LESS_THAN_OR_EQUAL_TO };
			}
			return (Token) { file, startPos, 1, TOKEN_LESS_THAN };

		case '>':
			if (fileGetChar(file, startPos + 1) == '>')
			{
				if (fileGetChar(file, startPos + 2) == '=')
				{
					return (Token) { file, startPos, 3, TOKEN_RIGHT_BIT_SHIFT_ASSIGN };
				}
				return (Token) { file, startPos, 2, TOKEN_RIGHT_BIT_SHIFT };
			}
			else if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TOKEN_GREATER_THAN_OR_EQUAL_TO };
			}
			return (Token) { file, startPos, 1, TOKEN_GREATER_THAN };

		case '%':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TOKEN_MODULUS_ASSIGN }
				: (Token) { file, startPos, 1, TOKEN_MODULUS };

		case '^':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TOKEN_BITWISE_XOR_ASSIGN }
				: (Token) { file, startPos, 1, TOKEN_BITWISE_XOR };
			
		case '&':
			if (fileGetChar(file, startPos + 1) == '&')
			{
				if (fileGetChar(file, startPos + 2) == '=')
				{
					return (Token) { file, startPos, 3, TOKEN_BOOLEAN_AND_ASSIGN };
				}
				return (Token) { file, startPos, 2, TOKEN_BOOLEAN_AND };
			}
			else if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TOKEN_BITWISE_AND_ASSIGN };
			}
			return (Token) { file, startPos, 1, TOKEN_AMPERSAND };

		case '*':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TOKEN_MULTIPLY_ASSIGN }
				: (Token) { file, startPos, 1, TOKEN_ASTERISK };

		case '-':
			if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TOKEN_SUBTRACT_ASSIGN };
			}
			else if (fileGetChar(file, startPos + 1) == '>')
			{
				return (Token) { file, startPos, 2, TOKEN_SINGLE_ARROW };
			}
			return (Token) { file, startPos, 1, TOKEN_MINUS };

		case '=':
			if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TOKEN_EQUALS };
			}
			else if (fileGetChar(file, startPos + 1) == '>')
			{
				return (Token) { file, startPos, 2, TOKEN_DOUBLE_ARROW };
			}
			return (Token) { file, startPos, 1, TOKEN_ASSIGN };

		case '|':
			if (fileGetChar(file, startPos + 1) == '|')
			{
				if (fileGetChar(file, startPos + 2) == '=')
				{
					return (Token) { file, startPos, 3, TOKEN_BOOLEAN_OR_ASSIGN };
				}
				return (Token) { file, startPos, 2, TOKEN_BOOLEAN_OR };
			}
			else if (fileGetChar(file, startPos + 1) == '=')
			{
				return (Token) { file, startPos, 2, TOKEN_BITWISE_OR_ASSIGN };
			}
			return (Token) { file, startPos, 1, TOKEN_PIPE };

		case '+':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TOKEN_ADD_ASSIGN }
				: (Token) { file, startPos, 1, TOKEN_PLUS };

		case '?':
			return (Token) { file, startPos, 1, TOKEN_QUESTION };

		case '!':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TOKEN_NOT_EQUALS }
				: (Token) { file, startPos, 1, TOKEN_BOOLEAN_NOT };

		case '/':
			return fileGetChar(file, startPos + 1) == '='
				? (Token) { file, startPos, 2, TOKEN_DIVIDE_ASSIGN }
				: (Token) { file, startPos, 1, TOKEN_SLASH };

		case '\'':
		case '\"':
			return getQuoteToken(file, startPos);

		default:
			exitWithError("An invalid character was found in the source file: '%c'.", fileGetChar(file, startPos));
	}
}

void incrementToken(Token *token)
{
	usize nextTokenPos = getNextPos(token->file, token->pos + token->length);

	*token = getNextToken(token->file, nextTokenPos);
}

Token getInitialToken(const File *file)
{
	usize pos = getNextPos(file, 0);

	return getNextToken(file, pos);
}

const char *tokenCategory(const Token *token)
{
	switch (token->type)
	{
		case TOKEN_END_OF_FILE:
			return "end-of-file";

		case TOKEN_IDENTIFIER:
			return "symbol";

		case TOKEN_LEFT_PARENTHESIS:
		case TOKEN_RIGHT_PARENTHESIS:
		case TOKEN_LEFT_BRACKET:
		case TOKEN_RIGHT_BRACKET:
		case TOKEN_LEFT_BRACE:
		case TOKEN_RIGHT_BRACE:
		case TOKEN_SEMICOLON:
		case TOKEN_COLON:
		case TOKEN_COMMA:
			return "separator";

		case TOKEN_DOT:
		case TOKEN_RANGE:
		case TOKEN_ELIPSIS:
		case TOKEN_AMPERSAND:
		case TOKEN_PIPE:
		case TOKEN_CARROT:
		case TOKEN_LEFT_BIT_SHIFT:
		case TOKEN_RIGHT_BIT_SHIFT:
		case TOKEN_BOOLEAN_NOT:
		case TOKEN_BOOLEAN_AND:
		case TOKEN_BOOLEAN_OR:
		case TOKEN_BITWISE_NOT:
		case TOKEN_BITWISE_XOR:
		case TOKEN_EQUALS:
		case TOKEN_NOT_EQUALS:
		case TOKEN_LESS_THAN_OR_EQUAL_TO:
		case TOKEN_GREATER_THAN_OR_EQUAL_TO:
		case TOKEN_LESS_THAN:
		case TOKEN_GREATER_THAN:
		case TOKEN_SINGLE_ARROW:
		case TOKEN_DOUBLE_ARROW:
		case TOKEN_OPTION:
		case TOKEN_QUESTION:
		case TOKEN_ASSIGN:
		case TOKEN_ADD_ASSIGN:
		case TOKEN_SUBTRACT_ASSIGN:
		case TOKEN_MULTIPLY_ASSIGN:
		case TOKEN_DIVIDE_ASSIGN:
		case TOKEN_MODULUS_ASSIGN:
		case TOKEN_LEFT_BIT_SHIFT_ASSIGN:
		case TOKEN_RIGHT_BIT_SHIFT_ASSIGN:
		case TOKEN_BITWISE_AND_ASSIGN:
		case TOKEN_BITWISE_OR_ASSIGN:
		case TOKEN_BITWISE_XOR_ASSIGN:
		case TOKEN_BOOLEAN_OR_ASSIGN:
		case TOKEN_BOOLEAN_AND_ASSIGN:
		case TOKEN_MODULUS:
		case TOKEN_SLASH:
		case TOKEN_ASTERISK:
		case TOKEN_PLUS:
		case TOKEN_MINUS:
		case TOKEN_SCOPE:
			return "operator";

		case TOKEN_INTEGER_LITERAL:
			return "integer literal";
		case TOKEN_FLOAT_LITERAL:
			return "float literal";
		case TOKEN_CHARACTER_LITERAL:
			return "character literal";
		case TOKEN_STRING_LITERAL:
			return "string literal";

		case TOKEN_KEYWORD_BREAK:
		case TOKEN_KEYWORD_CASE:
		case TOKEN_KEYWORD_CONTINUE:
		case TOKEN_KEYWORD_ELSE:
		case TOKEN_KEYWORD_ENUM:
		case TOKEN_KEYWORD_EXPORT:
		case TOKEN_KEYWORD_FALSE:
		case TOKEN_KEYWORD_FOR:
		case TOKEN_KEYWORD_FUNCTION:
		case TOKEN_KEYWORD_IF:
		case TOKEN_KEYWORD_IMPORT:
		case TOKEN_KEYWORD_LOOP:
		case TOKEN_KEYWORD_MATCH:
		case TOKEN_KEYWORD_MUT:
		case TOKEN_KEYWORD_PRIVATE:
		case TOKEN_KEYWORD_PUBLIC:
		case TOKEN_KEYWORD_RETURN:
		case TOKEN_KEYWORD_STRUCT:
		case TOKEN_KEYWORD_THEN:
		case TOKEN_KEYWORD_TRUE:
		case TOKEN_KEYWORD_TYPE:
		case TOKEN_KEYWORD_UNION:
		case TOKEN_KEYWORD_VAR:
		case TOKEN_KEYWORD_WHILE:
			return "keyword";

		default:
			exitWithError("Invalid TokenType: %d", token->type);
	}
}

char tokenGetChar(const Token *token, usize index)
{
	return fileGetChar(token->file, index);
}

char *tokenGetText(const Token *token)
{
	return fileGetText(token->file, token->pos, token->length);
}

usize tokenCopyText(char *out, const Token *token)
{
	fileCopyText(token->file, out, token->pos, token->length);

	return token->length;
}

bool tokenIsSame(const Token *a, const Token *b)
{
	// TODO: Do this? return memcmp(a, b, sizeof(Token)) == 0;

	bool isEqual = a->file == b->file
		&& a->pos == b->pos
		&& a->length == b->length
		&& a->type == b->type;

	return isEqual;
}
