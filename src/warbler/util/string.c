#include <warbler/util/string.h>
#include <warbler/util/memory.h>

#include <string.h>

String stringCreate()
{
    return (String) { NULL, 0, 0 };
}

String stringFrom(const char *text)
{
    usize length = strlen(text);

    char *data = allocate(length + 1);
    
    return (String) { data, length, length };
}

void stringFree(String *string)
{
    deallocate(string->data);
}

void stringReserve(String *string, usize capacity)
{
    if (string->capacity >= capacity)
        return;

    string->data = reallocate(string->data, capacity + 1);
    string->capacity = capacity;
}

void stringPushCString(String *string, const char* text)
{
    usize textLength = strlen(text);
    char *end = string->data + string->length;

    string->data = reallocate(string->data, string->length + textLength + 1);
    string->length += textLength;

    strcpy(end, text);
}

void stringPushCStringN(String *string, const char *text, usize n)
{
    char *end = string->data + string->length;

    string->data = reallocate(string->data, string->length + n + 1);
    string->length += n;

    memcpy(end, text, n);

    string->data[string->length] = '\0';
}

void stringPushChar(String *string, char c)
{
    string->data = reallocate(string->data, string->length + 2);
    string->length += 1;
    string->data[string->length - 1] = c;
    string->data[string->length] = '\0';
}
