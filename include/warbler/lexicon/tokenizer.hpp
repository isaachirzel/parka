#ifndef WARBLER_lEXICON_TOKENIZER_HPP
#define WARBLER_lEXICON_TOKENIZER_HPP

// #define MAX_KEYWORD_LENGTH (15)
// #define CHAR_TYPE_COUNT (128)
// #define TEMP_KEY_SIZE (1023)

// local includes
#include <warbler/lexicon/token.hpp>
#include <warbler/source/file.hpp>

// standard headers
#include <vector>

namespace warbler::lexicon
{
	void init_tokenizer();
	
	Result<Array<Token>> tokenize(const source::File& file);
}

#endif
