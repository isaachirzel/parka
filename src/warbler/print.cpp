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

#define PROMPT_NOTE			"note: "
#define PROMPT_WARNING		"warning: "
#define PROMPT_ERROR		"error: "

#define COLOR_NOTE		COLOR_CYAN
#define COLOR_WARNING	COLOR_PURPLE
#define COLOR_ERROR		COLOR_RED

#define PROMPT_NOTE_COLOR		COLOR_NOTE PROMPT_NOTE COLOR_RESET
#define PROMPT_WARNING_COLOR	COLOR_WARNING PROMPT_WARNING COLOR_RESET
#define PROMPT_ERROR_COLOR		COLOR_ERROR PROMPT_ERROR COLOR_RESET

namespace warbler
{
	std::ostream& error_stream = std::cout;
	static bool is_color_enabled = true;

	static inline const char *note_prompt()
	{
		return is_color_enabled
			? PROMPT_NOTE_COLOR
			: PROMPT_NOTE;
	}

	static inline const char *error_prompt()
	{
		return is_color_enabled
			? PROMPT_ERROR_COLOR
			: PROMPT_ERROR;
	}

	static inline const char *warning_prompt()
	{
		return is_color_enabled
			? PROMPT_WARNING_COLOR
			: PROMPT_WARNING;
	}

	void print_enable_color(bool enabled)
	{
		is_color_enabled = enabled;
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

		// std::cout << "(" << location.length() << ")\n";

		pos = location.pos_ptr() + location.length();

		while (true)
		{
			if (*pos == '\0' || *pos == '\n')
				break;

			out << *pos;
			pos += 1;
		}

		out << '\n' << std::string(2 + line_number_length, ' ') << "| ";
		
		std::string spacing = line_header;

		pos = location.start_of_line();

		for (usize i = 0; i < location.col(); ++i)
		{
			out << (pos[i] == '\t' ? '\t' : ' ');
		}

		if (is_color_enabled)
			out << color;

		// prints stray ~ so that there is at least one regardless of token length
		out << '~';

		for (usize i = 1; i < location.length(); ++i)
			out << '~';

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
		error_stream << error_prompt();

		return error_stream;
	}

	static void print_header(std::ostream& stream, const Location& location)
	{
		stream << location.filename() << ':' << location.line() + 1 << ':' << location.col() + 1 << ' ';
	}

	std::ostream& error_out(const Location& location)
	{
		print_header(error_stream, location);
		error_stream << error_prompt();

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
		print_error(iter->location(), "expected " + String(expected) + ", found '" + String(*iter) + '\'');
	}

	static void print_message(std::ostream& stream, const char *prompt, const char *color, const Location& location, const String& msg)
	{
		print_header(stream, location);

		if (is_color_enabled)
		{
			stream << color << prompt << COLOR_RESET;
		}
		else
		{
			stream << prompt;
		}

		stream << msg;
		
		highlight(stream, location, color);
	}

	void print_note(const Location& location, const String& msg)
	{
		print_message(error_stream, PROMPT_NOTE, COLOR_NOTE, location, msg); 
	}
	
	void print_warning(const Location& location, const String& msg)
	{
		print_message(error_stream, PROMPT_WARNING, COLOR_WARNING, location, msg);
	}

	void print_error(const Location& location, const String& msg)
	{
		print_message(error_stream, PROMPT_ERROR, COLOR_ERROR, location, msg); 
	}

	static void print_message(std::ostream& stream, const char *prompt, const char *color, const String& msg)
	{
		if (is_color_enabled)
		{
			stream << color << prompt << COLOR_RESET;
		}
		else
		{
			stream << prompt;
		}

		stream << msg << std::endl;
	}

	void print_note(const String& msg)
	{
		print_message(error_stream, PROMPT_NOTE, COLOR_NOTE, msg);
	}

	void print_warning(const String& msg)
	{
		print_message(error_stream, PROMPT_WARNING, COLOR_WARNING, msg);
	}

	void print_error(const String& msg)
	{
		print_message(error_stream, PROMPT_ERROR, COLOR_ERROR, msg);
	}

}