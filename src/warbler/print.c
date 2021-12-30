#include <warbler/print.h>


// standard headers
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

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

