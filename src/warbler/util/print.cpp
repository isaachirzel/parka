#include <warbler/util/print.hpp>

// standard headers
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <cstdlib>
#include <warbler/util/primitive.hpp>
#include <warbler/util/string.hpp>

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
	using source::Snippet;
	using source::Location;
	using lexicon::TokenIterator;

	std::ostream& output_stream = std::cout;
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

	void print_branch(u32 depth, const String& text)
	{
		if (depth > 0)
		{

			for (u32 i = 0; i < depth - 1; ++i)
				output_stream << "|   ";

			output_stream << "| > ";
		}

		output_stream << text << '\n';
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

	static inline print_margin(usize line = 0)
	{
		output_stream << ' ';

		if (line > 0)
		{
			usize size_of_num = get_spaces_for_num(line);
			usize spaces = 8 - size_of_num;

			output_stream << String(spaces, ' ') << line << " | ";

			
		}
		else
		{
			output_stream << "          | ";
		}
	}

	void print_snippet_highlight(const Snippet& snippet, const char *color)
	{
		Array<String> lines;

		for (usize i = 0; i < snippet.length(); ++i)
		{
			
		}

		while (true) // loop for each line
		{
			print_margin
		}

		for (usize

		for (usize i = 0; i < snippet.start_pos(); ++i)
			output_stream << snippet[i];

		if (is_color_enabled)
			output_stream << color;

		usize line = snippet.line();

		for (usize i = snippet.start_pos(); i < snippet.end_pos(); ++i)
		{
			auto character = snippet[i];
			output_stream << snippet[i];

			if (character == '\n')
			{
				line += 1;

			}
		}
		
		for (usize i = snippet.end_pos();

		const auto& data = snippet.data();

		for (usize i = snippet.start; i < snippet.pos(); ++i)
			output_stream << data[i];

		if (is_color_enabled)
			output_stream << color;

		usize end = snippet.pos() + snippet.length();

		for (usize i = snippet.pos(); i < 

		highlight.reserve(snippet.data().size() * 3)
		size_t line_number_length = get_spaces_for_num(snippet.line());	
		String line_header = snippet.data().substr(0, snippet.col());

		const char *text_after_location = location.end();
		const char *end = text_after_location;

		while (*end != '\0' && *end != '\n')
			end += 1;

		size_t footer_length = end - text_after_location;
		
		String line_footer(text_after_location, footer_length);
		line_footer += '\n';

		output_stream << "\n " << location.line() + 1 << " | ";

		const char *pos = location.start_of_line();
		for (usize i = 0; i < location.col(); ++i)
			output_stream << pos[i];

		if (is_color_enabled)
			output_stream << color;

		pos = location.pos_ptr();
		for (usize i = 0; i < location.length(); ++i)
			output_stream << pos[i];

		if (is_color_enabled)
			output_stream <<  COLOR_RESET;

		// std::cout << "(" << location.length() << ")\n";

		pos = location.pos_ptr() + location.length();

		while (true)
		{
			if (*pos == '\0' || *pos == '\n')
				break;

			output_stream << *pos;
			pos += 1;
		}

		output_stream << '\n' << String(2 + line_number_length, ' ') << "| ";
		
		String spacing = line_header;

		pos = location.start_of_line();

		for (usize i = 0; i < location.col(); ++i)
		{
			output_stream << (pos[i] == '\t' ? '\t' : ' ');
		}

		if (is_color_enabled)
			output_stream << color;

		// prints stray ~ so that there is at least one regardless of token length
		output_stream << '~';

		for (usize i = 1; i < location.length(); ++i)
			output_stream << '~';

		if (is_color_enabled)
			output_stream << COLOR_RESET;

		output_stream << '\n';
	}

	String tree_branch(u32 length)
	{
		String out;

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

	void print_parse_error(TokenIterator& iter, const String& expected)
	{
		print_error(iter->location(), "expected " + expected + ", found '" + iter->get_string() + '\'');
	}

	static void print_message(const char *prompt, const char *color, const Location& location, const String& msg)
	{
		auto snippet = location.get_snippet();

		output_stream << snippet.filename() << ':' << snippet.line() + 1 << ':' << snippet.col() + 1 << ' ';

		if (is_color_enabled)
		{
			output_stream << color << prompt << COLOR_RESET;
		}
		else
		{
			output_stream << prompt;
		}

		output_stream << msg;
		
		print_snippet_highlight(snippet, color);
	}

	void print_note(const Location& location, const String& msg)
	{
		print_message(PROMPT_NOTE, COLOR_NOTE, location, msg); 
	}
	
	void print_warning(const Location& location, const String& msg)
	{
		print_message(PROMPT_WARNING, COLOR_WARNING, location, msg);
	}

	void print_error(const Location& location, const String& msg)
	{
		print_message(PROMPT_ERROR, COLOR_ERROR, location, msg); 
	}

	void print_note(const String& msg)
	{
		print_message(PROMPT_NOTE, COLOR_NOTE, msg);
	}

	void print_warning(const String& msg)
	{
		print_message(PROMPT_WARNING, COLOR_WARNING, msg);
	}

	void print_error(const String& msg)
	{
		print_message(PROMPT_ERROR, COLOR_ERROR, msg);
	}

	std::runtime_error _not_implemented(const char *file, int line, const char *func)
	{
		return std::runtime_error(String(file) +  ":" + std::to_string(line) + " " + String(func) + "() is not implemented yet");
	}
}