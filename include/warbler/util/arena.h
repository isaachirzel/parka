#ifndef WARBLER_UTIL_ARENA_H
#define WARBLER_UTIL_ARENA_H

#include <warbler/util/primitives.h>

typedef struct Arena
{
	void *basePtr;
	usize pageCount;
	usize length;
} Arena;

Arena arenaCreate(usize maxBytes);
void arenaDestroy(Arena *arena);
void *arenaAllocate(Arena *arena, usize bytes);

#endif
