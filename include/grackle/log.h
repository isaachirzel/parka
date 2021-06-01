#ifndef LOG_H
#define LOG_H


extern void log_error_prompt(unsigned line, unsigned col);
extern void log_error(unsigned line, unsigned col, const char *error);
extern void log_set_filepath(const char *filepath);

#endif
