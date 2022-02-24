#include <warbler/lexicon/token.hpp>

namespace warbler::lexicon
{
	using source::File;
	using source::Location;
	using source::Snippet;

	
	Token::Token(const Location& location, TokenType type) :
	_location(location),
	_type(type)
	{}	

	bool Token::is_keyword()
	{
		switch (_type)
		{
			case TOKEN_KEYWORD_MUT:
				return true;

			case TOKEN_KEYWORD_FUNCTION:
				return true;

			case TOKEN_KEYWORD_VAR:
				return true;

			case TOKEN_KEYWORD_TYPE:
				return true;

			case TOKEN_KEYWORD_RETURN:
				return true;

			case TOKEN_KEYWORD_FOR:
				return true;

			case TOKEN_KEYWORD_WHILE:
				return true;

			case TOKEN_KEYWORD_LOOP:
				return true;

			case TOKEN_KEYWORD_CONTINUE:
				return true;

			case TOKEN_KEYWORD_BREAK:
				return true;

			case TOKEN_KEYWORD_IF:
				return true;

			case TOKEN_KEYWORD_THEN:
				return true;

			case TOKEN_KEYWORD_ELSE:
				return true;

			case TOKEN_KEYWORD_MATCH:
				return true;

			case TOKEN_KEYWORD_CASE:
				return true;

			case TOKEN_KEYWORD_STRUCT:
				return true;

			case TOKEN_KEYWORD_UNION:
				return true;

			case TOKEN_KEYWORD_ENUM:
				return true;

			case TOKEN_KEYWORD_TRUE:
				return true;

			case TOKEN_KEYWORD_FALSE:
				return true;

			case TOKEN_KEYWORD_IMPORT:
				return true;

			case TOKEN_KEYWORD_EXPORT:
				return true;

			case TOKEN_KEYWORD_PUBLIC:
				return true;

			case TOKEN_KEYWORD_PRIVATE:
				return true;

			default:
				return false;
		}
	}
}
