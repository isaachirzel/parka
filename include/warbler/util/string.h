#ifndef WARBLER_UTIL_STRING_H
#define WARBLER_UTIL_STRING_H

#include <warbler/util/primitives.h>

typedef struct String
{
	char *data;
	usize length;
	usize capacity;
} String;

typedef struct StringView
{
	const char *data;
	usize length;
} StringView;

String stringCreate();
String stringFrom(const char *text);
void stringClear(String *string);
void stringFree(String *string);
void stringReserve(String *string, usize capacity);
void stringConcat(String *string, const String *text);
void stringPushCString(String *string, const char *text);
void stringPushCStringN(String *string, const char *text, usize n);
void stringPushChar(String *string, char c);

#define stringPush(stringPtr, obj) ((_Generic((obj), const char *: stringPushCString, char *: stringPushCString, char: stringPushChar))(stringPtr, obj))

StringView stringViewFrom(const char *str, usize pos, usize length);

#endif
