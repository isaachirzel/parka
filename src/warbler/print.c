#include <warbler/print.h>

// standard headers
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

static const char *error_prompt = NULL;

void print_enable_color(bool enabled)
{
	if (enabled)
	{
		error_prompt = "\033[31merror:\033[0m ";
	}
	else
	{
		error_prompt = "\033[0merror: ";
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
	const char *end = file;

	while (end[1])
		++end;

	for (const char *pos = end; pos >= file; --pos)
	{
		if (pos[0] == 'a' && pos[1] == 's' && pos[2] == 't' && pos[3] == '/')
			return pos;
	}

	return file;
}

void _errorf(const char *file, unsigned line, const char *func, const char *fmt, ...)
{
	fprintf(stderr, "%s:%u:%s() %s", file, line, func, error_prompt);
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fputc('\n', stderr);
}

void _error(const char *file, unsigned line, const char *func, const char *msg)
{
	fprintf(stderr, "%s:%u:%s() %s%s\n", file, line, func, error_prompt, msg);
}

void _errort(const char *file, unsigned line, const char *func, const char *msg, const Token *token)
{
	fprintf(stderr, "%s:%u:%s() %s%s: ", file, line, func, error_prompt, msg);

	const String *str = &token->text;

	for (size_t i = 0; i < str->length; ++i)
	{
		fputc(str->data[i], stderr);
	}

	fputc('\n', stderr);
}

void _debugf(const char *file, unsigned line, const char *func, const char *fmt, ...)
{	
	fprintf(stderr, "%s[%u] %s(): ", get_shortened_file(file), line, func);
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fputc('\n', stderr);
}

void _debug(const char *file, unsigned line, const char *func, const char *msg)
{
	fprintf(stderr, "%s[%u] %s(): %s\n", get_shortened_file(file), line, func, msg);
}

