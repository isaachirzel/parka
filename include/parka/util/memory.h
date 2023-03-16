#ifndef PARKA_MEMORY_H
#define PARKA_MEMORY_H

#include "parka/util/primitives.h"

void *allocate(usize bytes);
void *reallocate(void *ptr, usize bytes);
void deallocate(void *ptr);
void *allocateArray(usize size, usize n);

#define makeArray(array, length) ((array) = allocateArray(sizeof(*(array)), (length)))
#define resizeArray(array, newSize) ((array) = reallocate((array), (newSize) * sizeof(*(array))))
#define new(type) ((type *)allocate(sizeof(type)))
#define makeNew(pointer) (pointer = allocate(sizeof(*pointer)))

void *_incrementArray(void *array, usize size, usize *length, usize *capacity);

#define incrementArray(array, length, capacity) ((array) = _incrementArray((array), sizeof(*(array)), (length), (capacity)))

#endif