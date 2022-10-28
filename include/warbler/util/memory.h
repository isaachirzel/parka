#ifndef WARBLER_MEMORY_H
#define WARBLER_MEMORY_H

#include <warbler/util/primitives.h>

void *allocate(usize bytes);
void *reallocate(void *ptr, usize bytes);
void deallocate(void *ptr);
char *duplicateString(const char *string);
char *duplicateStringN(const char *string, usize n);

#define makeArray(array, length) ((array) = allocate((length) * sizeof(*array)))
#define resizeArray(array, newSize) ((array) = reallocate((array), (newSize) * sizeof(*(array))))
#define new(type) ((type *)allocate(sizeof(type)))
#define makeNew(pointer) (pointer = allocate(sizeof(*pointer)))
#endif