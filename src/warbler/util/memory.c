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

char *duplicateString(const char *string)
{
    usize n = strlen(string);

    return duplicateStringN(string, n);
}

char *duplicateStringN(const char *string, usize n)
{
    char *data = allocate(n + 1);

    memcpy(data, string, n);

    return data;
}
