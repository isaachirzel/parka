#include <warbler/print.h>

void print_tabs(unsigned count)
{
	for (unsigned i = 0; i < count; ++i)
		putchar('\t');
}

void print_spaces(unsigned count)
{
	for (unsigned i = 0; i < count; ++i)
		putchar(' ');
}
