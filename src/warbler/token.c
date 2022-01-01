#include <warbler/token.h>

// standard headers
#include <stdio.h>
#include <assert.h>

Token token_default()
{
	return (Token) {
		.filename = NULL,
		.text = string_default(),
		.line = 0,
		.col = 0,
		.type = TOKEN_END_OF_FILE
	};
}

Token token_initial(const char *filename, const char *src)
{
	assert(filename);
	assert(src);
	
	return (Token) {
		.filename = filename,
		.text = (String)
		{
			.data = src,
			.length = 0
		},
		.line = 0,
		.col = 0,
		.type = TOKEN_END_OF_FILE
	};
}

Token token_eof(const char *filename)
{
	assert(filename);

	return (Token) {
		.filename = filename,
		.text = string_from("<end of file>"),
		.line = 0,
		.col = 0,
		.type = TOKEN_END_OF_FILE
	};
}

void token_print(const Token *self)
{
	assert(self);

	if (self->type == TOKEN_END_OF_FILE)
		fputs("<end of file>", stdout);
	else
		string_print(&self->text);
}

void token_println(const Token *self)
{
	token_print(self);
	putchar('\n');
}
