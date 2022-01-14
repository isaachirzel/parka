#include <warbler/token.hpp>

// standard headers
#include <cstdio>
#include <cassert>

namespace warbler
{
	Token::Token(const StringView& text, const char *filename, usize line, usize col, TokenType type) :
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

	Token Token::end_of_file(const char *filename, usize line, usize col)
	{
		return Token(StringView("<end of file>"), filename, line, col, TOKEN_END_OF_FILE);
	}

	std::ostream& operator<<(std::ostream& out, const Token& token)
	{
		out << token.text();

		return out;
	}
}
