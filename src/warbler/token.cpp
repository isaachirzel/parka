#include <warbler/token.hpp>

// standard headers
#include <cstdio>
#include <cassert>

namespace warbler
{
	Token::Token(const StringView& text, const String& filename, usize line, usize col, TokenType type) :
	_text(text),
	_filename(filename),
	_line(line),
	_col(col),
	_type(type)
	{}

	Token::Token() :
	_text(""),
	_filename(""),
	_line(0),
	_col(0),
	_type(TOKEN_END_OF_FILE)
	{}

	Token token_initial(const char *filename, const char *src)
	{
		assert(filename);
		assert(src);
		
		Token token = {
			filename,
			0,
			0,
			String {
				src, 0
			},
			TOKEN_END_OF_FILE
		};

		return token;
	}

	Token token_eof(const char *filename)
	{
		assert(filename);

		Token token =
		{
			filename,
			0,
			0,
			string_from("<end of file>"),
			TOKEN_END_OF_FILE
		};

		return token;
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
}
