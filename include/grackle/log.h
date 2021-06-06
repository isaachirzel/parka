#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

extern void log_error_prompt(unsigned line, unsigned col);
extern void log_error(unsigned line, unsigned col, const char *error);
extern void log_errorf(unsigned line, unsigned col, const char *fmt, ...);
extern void log_set_filepath(const char *filepath);

#endif
