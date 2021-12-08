#include <warbler/data/token.h>

#define DEFAULT_TEXT "<end of file>"
Token token_default()
{
	return (Token) {
		.string = (String) {
			.data = DEFAULT_TEXT,
			.length = sizeof(DEFAULT_TEXT) / sizeof(char) - 1
		},
		.line = 0,
		.col = 0,
		.type = TOKEN_END_OF_FILE
	};
}

