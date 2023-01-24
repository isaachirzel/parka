#include "warbler/util/array.h"
#include "warbler/util/memory.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

typedef Array(void) GenericArray;

// TODO: Make this bit agnostic
#define ARRAY_SIGNATURE (0x4849525A454C4152)

void arrayCreate(void *arrayPtr, usize elementSize, usize capacity)
{
	GenericArray *array = arrayPtr;
	void *buffer = capacity > 0
		? allocate(capacity * elementSize)
		: NULL;

	*array = (GenericArray)
	{
		.signature = ARRAY_SIGNATURE,
		.data = buffer,
		.elementSize = elementSize,
		.length = 0,
		.capacity = capacity,
	};
}

void arrayDestroy(void *arrayPtr, ElementDestructor destructor)
{
	GenericArray *array = arrayPtr;

	if (array->signature != ARRAY_SIGNATURE)
		return;

	if (destructor != NULL)
	{
		char *dataIter = array->data;

		for (usize i = 0; i < array->length; ++i)
		{
			destructor(dataIter);
			dataIter += array->elementSize;
		}
	}

	deallocate(array->data);
}

void arrayPush(void *arrayPtr, const void * restrict item)
{
	GenericArray *array = arrayPtr;

	assert(array->signature == ARRAY_SIGNATURE);
	assert(array->length <= array->capacity);

	if (array->length >= array->capacity)
		arrayReserve(array, array->capacity + 1);

	char *newElementPtr = (char*)array->data + (array->length * array->elementSize);

	memcpy(newElementPtr, item, array->elementSize);

	array->length += 1;
}

void arrayPop(void *arrayPtr)
{
	GenericArray *array = arrayPtr;

	assert(array->signature == ARRAY_SIGNATURE);
	assert(array->length > 0);

	array->length -= 1;
}

void arrayReserve(void *arrayPtr, usize capacity)
{
	GenericArray *array = arrayPtr;

	assert(array->signature == ARRAY_SIGNATURE);

	if (capacity <= array->capacity)
		return;

	usize newBufferSize = capacity * array->elementSize;

	array->data = reallocate(array->data, newBufferSize);
	array->capacity = capacity;
}

bool arrayForEach(void *arrayPtr, ElementAction action)
{
	GenericArray *array = arrayPtr;

	assert(array->signature == ARRAY_SIGNATURE);

	bool success = true;

	char *itemIter = array->data;

	for (usize i = 0; i < array->length; ++i)
	{
		if (!action(itemIter))
			success = false;

		itemIter += array->elementSize;
	}

	return success;
}
