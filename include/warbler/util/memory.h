#ifndef WARBLER_MEMORY_H
#define WARBLER_MEMORY_H

#include <warbler/util/primitives.h>

void *allocate(usize bytes);
void *reallocate(void *ptr, usize bytes);
void deallocate(void *ptr);
char *duplicateString(const char *string);
char *duplicateStringN(const char *string, usize n);

#define makeArray(array, length) ((array) = allocate((length) * sizeof(*array)))
#define arrayOf(type, length) (allocate(sizeof(type) * (length)))
#define resizeArray(array, newSize) ((array) = reallocate((array), (newSize) * sizeof(*(array))))
#define new(type) ((type *)allocate(sizeof(type)))
#define makeNew(pointer) (pointer = allocate(sizeof(*pointer)))

void *_incrementArray(void *array, usize size, usize *length, usize *capacity);

#define incrementArray(array, length, capacity) ((array) = _incrementArray((array), sizeof(*(array)), (length), (capacity)))

#endif