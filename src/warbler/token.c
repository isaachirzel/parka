#include <warbler/token.h>

#define DEFAULT_TEXT "<end of file>"
Token token_default()
{
	return (Token) {
		.string = STRING_FROM("<end of file>"),
		.line = 0,
		.col = 0,
		.type = TOKEN_END_OF_FILE
	};
}

