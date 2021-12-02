#ifndef WARBLER_TOKENIZER_H
#define WARBLER_TOKENIZER_H

// local includes
#include <warbler/data/token.h>

// standard library
#include <string>
#include <unordered_map>
#include <vector>

#define MAX_KEYWORD_LENGTH (15)
#define CHAR_TYPE_COUNT (128)

namespace warbler
{
	class Tokenizer
	{
	public:	// types

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

	private: // members

		std::unordered_map<std::string, Token::Type> _token_types;
		CharType _char_types[CHAR_TYPE_COUNT];

	public: // methods

		Tokenizer();
		Tokenizer(Tokenizer&&) = default;
		Tokenizer(const Tokenizer&) = default;
		~Tokenizer();

		std::vector<Token> tokenize(const char *src) const;
	};
}

#endif
