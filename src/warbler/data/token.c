#include <warbler/data/token.h>

Token token_default()
{
	return (Token) {
		.string = string_default(),
		.line = 0,
		.col = 0,
		.type = END_OF_FILE
	};
}

