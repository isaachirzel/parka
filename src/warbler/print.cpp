#include <warbler/print.hpp>

// standard headers
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cassert>
#include <iomanip>

#define COLOR_RED		"\033[91m"
#define COLOR_YELLOW 	"\033[93m"
#define COLOR_BLUE		"\033[94m"
#define COLOR_PURPLE	"\033[95m"
#define COLOR_CYAN		"\033[96m"
#define COLOR_RESET		"\033[0m"

#define PROMPT_ERROR		"error: "
#define PROMPT_FATAL		"fatal: "
#define PROMPT_DEBUG		"debug: "

#define PROMPT_ERROR_COLOR	COLOR_RED PROMPT_ERROR COLOR_RESET
#define PROMPT_FATAL_COLOR	COLOR_RED PROMPT_FATAL COLOR_RESET
#define PROMPT_DEBUG_COLOR	COLOR_BLUE PROMPT_DEBUG COLOR_RESET

namespace warbler
{
	std::ostream& error_stream = std::cout;

	static const char *error_prompt = PROMPT_ERROR_COLOR;
	static const char *fatal_prompt = PROMPT_FATAL_COLOR;
	static const char *debug_prompt = PROMPT_DEBUG_COLOR;
	static bool is_color_enabled = true;

	void print_enable_color(bool enabled)
	{
		is_color_enabled = enabled;

		if (enabled)
		{
			error_prompt = COLOR_RED PROMPT_ERROR COLOR_RESET;
			fatal_prompt = COLOR_RED PROMPT_FATAL COLOR_RESET;
			debug_prompt = COLOR_BLUE PROMPT_DEBUG COLOR_RESET;
		}
		else
		{
			error_prompt = PROMPT_ERROR;
			fatal_prompt = PROMPT_FATAL;
			debug_prompt = PROMPT_DEBUG;
		}	
	}

	void print_branch(unsigned count)
	{
		if (!count)
			return;

		for (unsigned i = 0; i < count - 1; ++i)
			fputs("|   ", stdout);

		fputs("| > ", stdout);
	}

	void print_spaces(unsigned count)
	{
		for (unsigned i = 0; i < count; ++i)
			putchar(' ');
	}

	static const char *get_shortened_file(const char *file)
	{

		for (const char *pos = file; *pos; pos += 1)
		{
			if (!strncmp(pos, "warbler/", 8))
				return pos + 8;
		}

		return file;
	}

	inline static void print_debug_header(const char *file, unsigned line, const char *func)
	{
		fprintf(stderr, "%s:%u:%s() ", get_shortened_file(file), line, func);
		fputs(debug_prompt, stderr);
	}

	size_t get_spaces_for_num(size_t number)
	{
		size_t out = 1;
		
		while (number > 9)
		{
			out += 1;
			number /= 10;
		}

		return out;
	}

	void highlight(std::ostream& out, const Location& location, const char *color)
	{
		size_t line_number_length = get_spaces_for_num(location.line());	
		std::string line_header(location.start_of_line(), location.col());

		const char *text_after_location = location.end();
		const char *end = text_after_location;

		while (*end != '\0' && *end != '\n')
			end += 1;

		size_t footer_length = end - text_after_location;
		
		std::string line_footer(text_after_location, footer_length);
		line_footer += '\n';

		out << "\n " << location.line() + 1 << " | ";

		const char *pos = location.start_of_line();
		for (usize i = 0; i < location.col(); ++i)
			out << pos[i];

		if (is_color_enabled)
			out << color;

		pos = location.pos_ptr();
		for (usize i = 0; i < location.length(); ++i)
			out << pos[i];

		if (is_color_enabled)
			out <<  COLOR_RESET;

		pos = location.pos_ptr() + location.length();

		for (pos = location.pos_ptr(); *pos != 0 && *pos != '\n'; ++pos)
			out << *pos;
		
		out << std::setw(2 + line_number_length) << "| ";
		
		std::string spacing = line_header;

		pos = location.start_of_line();
		for (usize i = 0; i < location.col(); ++i)
			out << (*pos == '\t' ? '\t' : ' ');

		if (is_color_enabled)
			out << color;

		out << '^';

		if (location.length() > 1)
		{
			auto length = location.length() - 1;

			for (usize i = 0; i < length; ++i)
				std::cout << '~';
		}

		if (is_color_enabled)
			out << COLOR_RESET;

		out << '\n';
	}

	void error_highlight(const Location& location)
	{
		highlight(error_stream, location, COLOR_RED);
	}

	void error_highlight(const TokenIterator& iter)
	{
		error_highlight(iter->location());
	}

	void error_highlight(const Token& token)
	{
		error_highlight(token.location());
	}

	void message_highlight(const Location& location)
	{
		highlight(error_stream, location, COLOR_CYAN);
	}

	void warning_highlight(const Location& location)
	{
		highlight(error_stream, location, COLOR_PURPLE);
	}

	std::ostream& error_out()
	{
		error_stream << error_prompt;

		return error_stream;
	}

	std::ostream& error_out(const Location& location)
	{
		error_stream << location.filename() << ':' << location.line() + 1 << ':' << location.col() + 1 << ' ' << error_prompt;

		return error_stream;
	}

	std::ostream& error_out(const Token& token)
	{
		return error_out(token.location());
	}

	std::ostream& error_out(TokenIterator& iter)
	{
		return error_out(iter->location());
	}

	std::string tree_branch(u32 length)
	{
		std::string out;

		if (length == 0)
			return "";

		out.resize(length * 4);
		
		length *= 4;

		for (u32 i = 0; i < length; i += 4)
		{
			out[i]     = '|';
			out[i + 1] = ' ';
			out[i + 2] = ' ';
			out[i + 3] = ' ';
		}

		out[out.size() - 2] = '>';

		return out;
	}

	void parse_error(TokenIterator& iter, const char *expected)
	{
		error_out(iter) << "expected " << expected << " but got '" << *iter << '\'';
		error_highlight(iter);
	}
}