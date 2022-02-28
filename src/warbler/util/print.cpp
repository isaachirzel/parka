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
#define COLOR_YELLOW	"\033[93m"
#define COLOR_BLUE		"\033[94m"
#define COLOR_PURPLE	"\033[95m"
#define COLOR_CYAN		"\033[96m"
#define COLOR_RESET		"\033[0m"

#define PROMPT_NOTE		"note: "
#define PROMPT_WARNING	"warning: "
#define PROMPT_ERROR	"error: "

namespace warbler
{
	using source::Snippet;
	using source::Location;
	using lexicon::TokenIterator;

	std::ostream& output_stream = std::cout;
	static bool is_color_enabled = true;

	enum class LogLevel
	{
		Note,
		Warning,
		Error
	};

	struct LogContext
	{
		const char * const prompt;
		const char * const color;
		const char * const reset;

		LogContext() :
		prompt(""),
		color(""),
		reset("")
		{}

		LogContext(const char *prompt) :
		prompt(prompt),
		color(""),
		reset("")
		{}

		LogContext(const char *prompt, const char *color) :
		prompt(prompt),
		color(color),
		reset(COLOR_RESET)
		{}
	};

	LogContext get_log_context(LogLevel level)
	{
		if (is_color_enabled)
		{
			switch (level)
			{
				case LogLevel::Note:
					return { PROMPT_NOTE, COLOR_CYAN };
				case LogLevel::Warning:
					return { PROMPT_WARNING, COLOR_PURPLE };
				case LogLevel::Error:
					return { PROMPT_ERROR, COLOR_RED };
			}
		}
		else
		{
			switch (level)
			{
				case LogLevel::Note:
					return { PROMPT_NOTE };
				case LogLevel::Warning:
					return { PROMPT_WARNING };
				case LogLevel::Error:
					return { PROMPT_ERROR };
			} 
		}

		return {};
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

	// static const char *get_shortened_file(const char *file)
	// {

	// 	for (const char *pos = file; *pos; pos += 1)
	// 	{
	// 		if (!strncmp(pos, "warbler/", 8))
	// 			return pos + 8;
	// 	}

	// 	return file;
	// }

	size_t get_number_width(size_t number)
	{
		size_t out = 1;
		
		while (number > 9)
		{
			out += 1;
			number /= 10;
		}

		return out;
	}

	String get_margin(usize line_number_padding, usize line = 0)
	{
		String margin;

		const usize margin_padding_spaces = 4;
		const usize margin_size = line_number_padding + margin_padding_spaces;

		margin.reserve(margin_size);

		if (line > 0)
		{
			usize number_padding_spaces = line_number_padding - get_number_width(line) + 1;
		
			margin += String(number_padding_spaces, ' ');
			margin += std::to_string(line);
			margin += " | ";
		}
		else
		{
			margin.resize(margin_size, ' ');
			margin[margin_size - 2] = '|';
		}

		return margin;
	}

	String get_snippet_highlight(const Snippet& snippet, const LogContext& context)
	{
		assert(snippet.lines().size() > 0);

		usize length = 0;

		for (const auto& line : snippet.lines())
			length += line.length();

		String highlight;
		
		usize line_number_width = get_number_width(snippet.line() + snippet.lines().size() - 1);

		highlight.reserve(length * 3);

		usize current_line_number = snippet.line();

		for (const auto& line : snippet.lines())
		{
			String line_text = line;
			String underline_text;

			line_text.reserve(line.size() + 8); // extra padding for color codes & newline
			underline_text.reserve(line.capacity());

			line_text += get_margin(line_number_width, current_line_number);
			underline_text += get_margin(line_number_width);

			for (usize i = 0; i < line.size(); ++i)
			{
				auto is_first_line = &line == &snippet.lines().front();
				auto is_last_line = &line == &snippet.lines().back();

				if (is_first_line && i == snippet.start_pos())
				{
					line_text += context.color;
					underline_text += context.color;
				}
				else if (is_last_line && i == snippet.end_pos())
				{	
					line_text += context.reset;
					underline_text += context.reset;
				}
			}

			String empty_line_text = get_margin(line_number_width);

			empty_line_text += '\n';
			line_text += '\n';
			underline_text += '\n';

			highlight += empty_line_text;
			highlight += line_text;
			highlight += underline_text;

			current_line_number += 1;
		}

		return highlight;
	}

	String tree_branch(u32 length)
	{
		if (length == 0)
			return "";

		length *= 4;

		String out(length, ' ');

		for (u32 i = 0; i < length; i += 4)
			out[i] = '|';

		out[out.size() - 2] = '>';

		return out;
	}

	void print_parse_error(TokenIterator& iter, const String& expected)
	{
		print_error(iter->location(), "expected " + expected + ", found '" + iter->get_string() + '\'');
	}

	static inline void print_message(const LogContext& context, const String& msg)
	{
		output_stream << context.color << context.prompt << context.reset << msg << '\n';
	}

	static void print_message(LogLevel level, const Snippet& snippet, const String& msg)
	{
		output_stream << snippet.filename() << ':' << snippet.line() + 1 << ':' << snippet.col() + 1 << ' ';

		auto context = get_log_context(level);

		print_message(context, msg);

		output_stream << get_snippet_highlight(snippet, context);
	}

	void print_note(const Snippet& snippet, const String& msg)
	{
		print_message(LogLevel::Note, snippet, msg);
	}

	void print_warning(const Snippet& snippet, const String& msg)
	{
		print_message(LogLevel::Warning, snippet, msg);
	}

	void print_error(const Snippet& snippet, const String& msg)
	{
		print_message(LogLevel::Error, snippet, msg);
	}

	void print_note(const Location& location, const String& msg)
	{
		print_message(LogLevel::Note, location.get_snippet(), msg);
	}
	
	void print_warning(const Location& location, const String& msg)
	{
		print_message(LogLevel::Warning, location.get_snippet(), msg);
	}

	void print_error(const Location& location, const String& msg)
	{
		print_message(LogLevel::Error, location.get_snippet(), msg);
	}

	void print_note(const String& msg)
	{
		print_message(get_log_context(LogLevel::Note), msg);
	}

	void print_warning(const String& msg)
	{
		print_message(get_log_context(LogLevel::Warning), msg);
	}

	void print_error(const String& msg)
	{
		print_message(get_log_context(LogLevel::Error), msg);
	}

	std::runtime_error _not_implemented(const char *file, int line, const char *func)
	{
		return std::runtime_error(String(file) +  ":" + std::to_string(line) + " " + String(func) + "() is not implemented yet");
	}
}
