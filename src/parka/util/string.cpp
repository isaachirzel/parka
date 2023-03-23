#include "parka/util/string.hpp"


#include <string.h>
#include <stdio.h>
#include <assert.h>

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

usize stringFindOccurrence(const char *text, const char *token)
{
    assert(text != NULL);
    assert(token != NULL);

    char starter = token[0];
    usize length = strlen(token);

    for (const char *iter = text; *iter; ++iter)
    {
        if (*iter != starter)
            continue;

        if (!strncmp(iter, token, length))
            return iter - text;
    }

    return SIZE_MAX;
}

StringBuilder sbCreate(usize capacity)
{
    char *buffer = allocate(capacity + 1);

    buffer[0] = '\0';

    StringBuilder builder =
    {
        .data = buffer,
        .length = 0,
        .capacity = capacity
    };

    return builder;
}

StringBuilder sbFrom(const char *text)
{
    usize length = strlen(text);
    char *data = allocate(length + 1);

    memcpy(data, text, length);
    data[length] = 0;
    
    StringBuilder string =
    {
        .data = data,
        .length = length,
        .capacity = length
    };

    return string;
}

void sbDestroy(StringBuilder *string)
{
    deallocate(string->data);
}

void sbReserve(StringBuilder *string, usize capacity)
{
    if (string->capacity >= capacity)
        return;

    string->data = reallocate(string->data, capacity + 1);
    string->capacity = capacity;
}

void sbPushString(StringBuilder *string, const char* text)
{
    usize textLength = strlen(text);

    sbPushStringN(string, text, textLength);
}

void sbPushStringN(StringBuilder *string, const char *text, usize n)
{
    usize newLength = string->length + n;

    sbReserve(string, newLength);

    char *end = string->data + string->length;

    memcpy(end, text, n);

    string->data[newLength] = '\0';
    string->length = newLength;
}

void sbPushChar(StringBuilder *sb, char c)
{
    sbReserve(sb, sb->length + 1);

    sb->data[sb->length] = c;
    sb->length += 1;
    sb->data[sb->length] = '\0';
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

void sbClear(StringBuilder *string)
{
    string->length = 0;
}

const char *sbPushLine(StringBuilder *sb, const char *text)
{
    usize length = 0;

    for (const char *iter = text; *iter && *iter != '\n'; ++iter)
        length += 1;
        
    sbReserve(sb, sb->length + length);

    char *buffer = sb->data + sb->length;

    sb->length += length;

    memcpy(buffer, text, length);

    buffer[sb->length] = '\0';

    return text + length;
}

void sbPushCharN(StringBuilder *sb, char c, usize n)
{
    sbReserve(sb, sb->length + n);

    usize newLength = sb->length + n;

    for (usize i = sb->length; i < newLength; ++i)
        sb->data[i] = c;

    sb->length = newLength;
    sb->data[newLength] = '\0';
}

void sbConcat(StringBuilder *string, const StringBuilder *text)
{
    sbPushStringN(string, text->data, text->length);
}

void sbPushStringInvisible(StringBuilder *sb, const char *text)
{
    usize n = strlen(text);

    sbPushStringInvisibleN(sb, text, n);
}

void sbPushStringInvisibleN(StringBuilder *sb, const char *text, usize n)
{
    usize newLength = sb->length + n;

    sbReserve(sb, newLength);

    for (usize i = 0; i < n; ++i)
    {
        usize index = sb->length + i;

        sb->data[index] = text[i] == '\t' ? '\t' : ' ';
    }

    sb->data[newLength] = '\0';
    sb->length = newLength;
}
