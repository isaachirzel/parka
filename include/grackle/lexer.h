#ifndef GRACKLE_LEXER_H
#define GRACKLE_LEXER_H

// local includes
#include <grackle/data/token.h>

// standard library
#include <unordered_map>

namespace grackle
{
	enum CharType
	{
		NONE,
		INVALID,
		IDENTIFIER,
		SEPARATOR,
		DOT,
		DIGIT,
		OPERATOR,
		QUOTE
	};

	class Lexer
	{
	private:

		static bool _is_lexer_initialized;
		static std::unordered_map<std::string_view, Token::Type> _token_types;
		static char _char_types[128];

	public:

		static constexpr const unsigned max_keyword_length = 15;

	public:

		Lexer();

		std::vector<Token> lex(const char *src);
	};
}

#endif
