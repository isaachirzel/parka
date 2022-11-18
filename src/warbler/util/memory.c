#include <warbler/util/memory.h>
#include <warbler/util/print.h>

#include <stdlib.h>
#include <string.h>

static const char *allocationError = "The process ran out of memory";

void *allocate(usize bytes)
{
	void *ptr = malloc(bytes);

	if (!ptr)
	{
		printError(allocationError);
		exit(EXIT_FAILURE);
	}

	return ptr;
}

void *reallocate(void *ptr, usize bytes)
{
	void *tmp = realloc(ptr, bytes);

	if (!tmp)
	{
		printError(allocationError);
		exit(EXIT_FAILURE);
	}

	return tmp;
}

void deallocate(void *ptr)
{
	free(ptr);
}

char *stringDuplicate(const char *string)
{
	assert(string);
	usize n = strlen(string);

	return stringDuplicateN(string, n);
}

char *stringDuplicateN(const char *string, usize n)
{
	assert(string);
	char *data = allocate(n + 1);

	memcpy(data, string, n);

	data[n] = '\0';

	return data;
}

void *_incrementArray(void *array, usize size, usize * restrict length, usize * restrict capacity)
{
	if (*length < *capacity)
	{
		*length += 1;

		return array;
	}

	*capacity = *length + 1;
	*length += 1;

	return reallocate(array, size * *capacity);
}

void *allocateArray(usize size, usize length)
{
	return calloc(length, size);
}