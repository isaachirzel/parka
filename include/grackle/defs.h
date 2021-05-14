#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>

// Errors
typedef const char* Error;

#define MALLOC_ERROR	"failed to allocate buffer"
#define RESIZE_ERROR	"failed to resize buffer"
#define FOPEN_ERROR		"failed to read file"

// String handling
typedef char* String;

typedef struct StringView
{
	const char *ptr;
	uint16_t len;
} StringView;

#endif
