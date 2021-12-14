#ifndef WARBLER_PROGRAM_H
#define WARBLER_PROGRAM_H

#include <warbler/ast/function.h>

typedef struct
{
	Function *functions;
	size_t count;
} Program;

Error program_parse(Program *out, TokenIterator *iter);
void program_free(Program *program);

#endif
