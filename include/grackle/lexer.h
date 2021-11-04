#ifndef GRACKLE_LEXER_H
#define GRACKLE_LEXER_H

// local includes
#include <grackle/data/token.h>

// standard library
#include <vector>
#include <string_view>
#include <unordered_map>

namespace grackle
{
	namespace lexer
	{
		enum CharType
		{
			INVALID,
			IDENTIFIER,
			SEPARATOR,
			DOT,
			DIGIT,
			OPERATOR,
			QUOTE
		};	

		inline unsigned max_keyword_length = 15;

		extern void initialize();
		extern std::vector<Token> tokenize(const char *src);
	}
}

#endif
