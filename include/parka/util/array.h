#ifndef PARKA_UTIL_ARRAY_H
#define PARKA_UTIL_ARRAY_H

#include "parka/util/primitives.h"

typedef void (*ElementDestructor)(void *);
typedef bool (*ElementAction)(void *);

#define Array(type) struct\
{\
	usize signature;\
	type *data;\
	usize elementSize;\
	usize length;\
	usize capacity;\
}

typedef Array(usize) IndexList;

void arrayCreate(void *array, usize elementSize, usize capacity);
#define arrayInit(array, capacity) (arrayCreate(array, sizeof(*(array)->data), capacity))
void arrayDestroy(void *array, ElementDestructor destructor);
usize arrayPush(void *array, const void * restrict item);
void arrayPop(void *array);
void arrayReserve(void *array, usize capacity);
bool arrayForEach(void *array, ElementAction action);

#endif
