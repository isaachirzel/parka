#include <grackle/log.h>

#include <stdio.h>

const char *curr_filepath;

void log_error(token_t *tok, const char *msg)
{
	fprintf(stderr, "%s:%u:%u:  error: %s\n", curr_filepath, tok->line, tok->col, msg);
}

void log_parse_error(token_t *tok, const char *expected)
{
	fprintf(stderr, "%s:%u:%u:  error: expected %s before '", curr_filepath,
		tok->line, tok->col, expected);

	for (unsigned i = 0; i < tok->str.len; ++i)
	{
		putc(tok->str.ptr[i], stderr);
	}
	fputs("'\n", stderr);
}	

void log_set_filepath(const char *filepath)
{
	curr_filepath = filepath;
}
