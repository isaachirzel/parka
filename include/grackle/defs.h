#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>

// Errors
typedef const char* Error;

Error MALLOC_ERROR	= "failed to allocate buffer";
Error RESIZE_ERROR	= "failed to resize buffer";
Error FOPEN_ERROR	= "failed to read file";

// String handling
typedef char * String;

typedef struct StringView
{
	const String str;
	uint16_t len;
} StringView;


#endif
