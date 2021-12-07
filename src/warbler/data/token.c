#include <warbler/data/token.h>

Token token_default()
{
	return (Token) {
		.string = string_default(),
		.line = 0,
		.col = 0,
		.type = TOKEN_END_OF_FILE
	};
}

