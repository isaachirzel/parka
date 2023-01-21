#ifndef WARBLER_UTIL_ARENA_H
#define WARBLER_UTIL_ARENA_H

#include "warbler/util/primitives.h"

typedef struct Arena
{
	void *data;
	usize pageCount;
	usize committedPages;
	usize bytesUsed;
} Arena;

Arena arenaCreate(usize minBytes);
void arenaDestroy(Arena *arena);
void *arenaAllocate(Arena *arena, usize bytes);

#endif
