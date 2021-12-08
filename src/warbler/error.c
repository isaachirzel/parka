#include <warbler/error.h>

// standard library
#include <stdio.h>
#include <stdarg.h>

const char * const error_prompt_color	= "\033[31merror:\033[0m ";
const char * const error_prompt_plain	= "error: ";
bool is_color_enabled = true;
bool is_printing_enabled = true;

void set_color_enabled(bool enabled)
{
	is_color_enabled = enabled;
}

void set_printing_enabled(bool enabled)
{
	is_printing_enabled = enabled;
}

const char *get_error_prompt()
{
	return is_color_enabled
		? error_prompt_color
		: error_prompt_plain;
}

void print_error(const char *msg)
{
	const char *error_prompt = get_error_prompt();

	printf("%s%s\n", error_prompt, msg);
}

void print_errorf(const char *fmt, ...)
{
	const char *error_prompt = get_error_prompt();

	va_list arg_list;
	va_start(arg_list, fmt);
	fputs(error_prompt, stdout);
	vprintf(fmt, arg_list);
	putchar('\n');
}
