#include <grackle/log.h>

#include <stdio.h>

const char *curr_filepath;

void log_error(token_t *tok, const char *msg)
{
	fprintf(stderr, "%s:%u:%u:  error: %s\n", curr_filepath, tok->line, tok->col, msg);
}

void log_set_filepath(const char *filepath)
{
	curr_filepath = filepath;
}
