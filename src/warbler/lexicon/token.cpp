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
			case TokenType::KeywordMut:
				return true;

			case TokenType::KeywordFunction:
				return true;

			case TokenType::KeywordVar:
				return true;

			case TokenType::KeywordType:
				return true;

			case TokenType::KeywordReturn:
				return true;

			case TokenType::KeywordFor:
				return true;

			case TokenType::KeywordWhile:
				return true;

			case TokenType::KeywordLoop:
				return true;

			case TokenType::KeywordContinue:
				return true;

			case TokenType::KeywordBreak:
				return true;

			case TokenType::KeywordIf:
				return true;

			case TokenType::KeywordThen:
				return true;

			case TokenType::KeywordElse:
				return true;

			case TokenType::KeywordMatch:
				return true;

			case TokenType::KeywordCase:
				return true;

			case TokenType::KeywordStruct:
				return true;

			case TokenType::KeywordUnion:
				return true;

			case TokenType::KeywordEnum:
				return true;

			case TokenType::KeywordTrue:
				return true;

			case TokenType::KeywordFalse:
				return true;

			case TokenType::KeywordImport:
				return true;

			case TokenType::KeywordExport:
				return true;

			case TokenType::KeywordPublic:
				return true;

			case TokenType::KeywordPrivate:
				return true;

			default:
				return false;
		}
	}
}
