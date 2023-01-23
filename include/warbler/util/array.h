#ifndef WARBLER_UTIL_ARRAY_H
#define WARBLER_UTIL_ARRAY_H

#include "warbler/util/primitives.h"

#define Array(type) struct\
{\
	usize signature;\
	type *data;\
	usize elementSize;\
	usize length;\
	usize capacity;\
}

typedef void (*ElementDestructor)(void *);

void arrayCreate(void *array, usize elementSize, usize capacity);
void arrayDestroy(void *array, ElementDestructor destructor);
void arrayPush(void *array, const void * restrict item);
void arrayPop(void *array);
void arrayReserve(void *array, usize capacity);

#endif
