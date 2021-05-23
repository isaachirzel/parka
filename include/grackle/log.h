#ifndef LOG_H
#define LOG_H

#include <grackle/token.h>

void log_error(token_t *tok, const char *msg);
void log_parse_error(token_t *tok, const char *expected);

void log_set_filepath(const char *filepath);

#endif
