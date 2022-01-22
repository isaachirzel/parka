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

	static void fprint_message(FILE *stream, const char *prompt, const char *msg)
	{
		fprintf(stream, "%s%s\n", prompt, msg);
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

	static void vftprintf(FILE *stream, const char *fmt, va_list args)
	{
		char switch_tmp[8];
		
		const char *pos = fmt;

		while (*pos)
		{
			const char * const start = pos;

			// go to next switch
			while (*pos != '\0' && *pos != '%')
				++pos;

			const char * const switch_ptr = pos;

			if (switch_ptr - start > 0)
			{
				fwrite(start, sizeof(char), switch_ptr - start, stream);
			}

			if (*switch_ptr == '\0')
				break;

			while (*pos > ' ')		
				++pos;

			size_t size_of_switch = pos - switch_ptr;
			assert(size_of_switch < 8);

			for (size_t i = 0; i < size_of_switch; ++i)
				switch_tmp[i] = switch_ptr[i];

			switch_tmp[size_of_switch] = '\0';

			if (switch_tmp[1] == 't')
			{
				assert(size_of_switch == 2);
				Token *token = va_arg(args, Token *);
				std::cerr << token->text();				
			}
			else
			{
				vfprintf(stream, switch_tmp, args);
			}
		}
	}

	void ftprintf(FILE *stream, const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		vfprintf(stream, fmt, args);
		va_end(args);
	}

	void tprintf(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		vftprintf(stdout, fmt, args);
		va_end(args);
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

	static std::string token_highlight(TokenIterator& iter, const char *color)
	{
		const auto& token = *iter;

		size_t spaces_for_line_number = get_spaces_for_num(token.line());
		const char * const start_of_line = token.text().data() - token.col();
		std::string line_header(start_of_line, token.col());

		const char *text_after_token = token.text().data() + token.text().size();
		const char *end = text_after_token;

		while (*end != '\0' && *end != '\n')
			end += 1;

		size_t footer_length = end - text_after_token;
		
		std::string line_footer(text_after_token, footer_length);
		line_footer += '\n';

		std::string out = "\n " + std::to_string(token.line() + 1) + " | " + line_header;

		if (is_color_enabled)
			out += color;
		
		out += token.text();

		if (is_color_enabled)
			out += COLOR_RESET;

		out += line_footer + std::string(2 + spaces_for_line_number, ' ') + "| ";
		
		std::string spacing = line_header;
	
		for (char& c : spacing)
		{
			if (c != '\t')
				c = ' ';
		}
			
		out += spacing;

		if (is_color_enabled)
			out += color;

		std::string underline = "^";

		if (token.text().size() > 1)
			underline += std::string(token.text().size() - 1, '~');

		out += std::move(underline);

		if (is_color_enabled)
			out += COLOR_RESET;

		out += '\n';

		return out;
	}

	std::string token_error(TokenIterator& iter)
	{
		return token_highlight(iter, COLOR_RED);
	}

	std::string token_warning(TokenIterator& iter)
	{
		return token_highlight(iter, COLOR_PURPLE);
	}

	std::string token_message(TokenIterator& iter)
	{
		return token_highlight(iter, COLOR_BLUE);
	}

	std::ostream& error_out()
	{
		std::cout << error_prompt;

		return std::cout;
	}

	std::ostream& error_out(const Location& location)
	{
		std::cout << location.filename() << ':' << location.line() + 1 << ':' << location.col() + 1 << ' ' << error_prompt;

		return std::cout;
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
		error_out(iter) << "expected " << expected << " but got '" << *iter << '\'' << token_error(iter) << std::endl;
	}
}