#ifndef WARBLER_ERROR_H
#define WARBLER_ERROR_H

#include <stdbool.h>

extern bool is_color_output;
extern void print_error(const char *msg);
extern void print_errorf(const char *fmt, ...);

#define notImplementedError() print_errorf("%s is not implemented yet", __func__)

#endif
