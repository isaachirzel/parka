#include <warbler/print.hpp>

// standard headers
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cassert>

#define COLOR_BLUE		"\033[94m"
#define COLOR_RED		"\033[91m"
#define COLOR_YELLOW 	"\033[93m"
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

	void print_tree_branch_symbol(const char *symbol, unsigned depth)
	{
		print_branch(depth);
		puts(symbol);
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

	std::ostream& token_highlight(const Token& token)
	{
		size_t spaces_for_line_number = get_spaces_for_num(token.line());
		const char * const start_of_line = token.text().data() - token.col();
		fprintf(stderr, "  %zu | ", token.line());
		fwrite(start_of_line, sizeof(char), token.col(), stderr);	
		fputs(COLOR_RED, stderr);
		fwrite(token.text().data(), sizeof(char), token.text().size(), stderr);
		fputs(COLOR_RESET, stderr);

		const char *text_after_token = token.text().data() + token.text().size();
		const char *end = text_after_token;
		while (*end != '\0' && *end != '\n')
			++end;

		size_t length_after_token = end - text_after_token;

		fwrite(text_after_token, sizeof(char), length_after_token, stderr);
		fputc('\n', stderr);

		fputs("  ", stderr);
		for (size_t i = 0; i < spaces_for_line_number; ++i)
			fputc(' ', stderr);
		fputs(" | ", stderr);
		for (size_t i = 0; i < token.col(); ++i)
			fputc(' ', stderr);
		
		if (is_color_enabled)
			fputs(COLOR_RED, stderr);

		fputc('^', stderr);
		for (size_t i = 1; i < token.text().size(); ++i)
			fputc('~', stderr);

		if (is_color_enabled)
			fputs(COLOR_RESET, stderr);

		fputc('\n', stderr);
	}

	std::ostream& error_out()
	{
		std::cout << error_prompt;

		return std::cout;
	}

	std::ostream& error_out(const Token& token)
	{
		std::cout <<  token.filename() << ':' << token.line() << ':' << token.col() << error_prompt;

		return std::cout;
	}

	std::ostream& error_out(TokenIterator& iter)
	{
		return error_out(*iter);
	}
}