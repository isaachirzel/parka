#ifndef WARBLER_PRINT_H
#define WARBLER_PRINT_H

void print_branch(unsigned count);
void print_spaces(unsigned count);

void _debugf(const char *file, unsigned line, const char *func, const char *fmt, ...);
void _debug(const char *file, unsigned line, const char *func, const char *msg);

#ifndef NDEBUG
	#define debugf(fmt, ...) _debugf(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
	#define debug(msg) _debug(__FILE__, __LINE__, __func__, msg)
#else
	#define debugf(fmt, ...)
	#define debug(msg)
#endif

#endif
