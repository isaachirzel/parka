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

    memcpy(data, text, length);
    data[length] = 0;
    
    String string =
    {
        .data = data,
        .length = length,
        .capacity = length
    };

    return string;
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

    stringPushCStringN(string, text, textLength);
}

void stringPushCStringN(String *string, const char *text, usize n)
{
    usize newLength = string->length + n;

    string->data = reallocate(string->data, newLength + 1);

    char *end = string->data + string->length;

    string->length = newLength;
    string->capacity = newLength;

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

StringView stringViewFrom(const char *str, usize pos, usize length)
{
    StringView text =
    {
        .data = str + pos,
        length = length
    };

    return text;
}

void stringClear(String *string)
{
    string->length = 0;
}

void stringConcat(String *string, const String *text)
{
    stringPushCStringN(string, text->data, text->length);
}
