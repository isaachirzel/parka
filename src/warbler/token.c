#include <warbler/token.h>

#define DEFAULT_TEXT "<end of file>"
Token token_default()
{
	return (Token) {
		.text = STRING_FROM("<end of file>"),
		.line = 0,
		.col = 0,
		.type = TOKEN_END_OF_FILE
	};
}

void token_print(const Token *self)
{
	string_print(&self->text);
}

void token_println(const Token *self)
{
	string_println(&self->text);
}
