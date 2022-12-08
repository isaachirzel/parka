#ifndef WARBLER_UTIL_STRING_H
#define WARBLER_UTIL_STRING_H

#include <warbler/util/primitives.h>

typedef struct StringBuilder
{
	char *data;
	usize length;
	usize capacity;
} StringBuilder;

typedef struct StringView
{
	const char *data;
	usize length;
} StringView;

StringBuilder sbCreate(usize length);
StringBuilder stringFrom(const char *text);
void sbClear(StringBuilder *string);
void sbDestroy(StringBuilder *string);
void sbReserve(StringBuilder *string, usize capacity);
void sbConcat(StringBuilder *string, const StringBuilder *text);
const char *sbPushLine(StringBuilder *sb, const char *text);
void sbPushString(StringBuilder *string, const char *text);
void sbPushStringN(StringBuilder *string, const char *text, usize n);
void sbPushStringInvisible(StringBuilder *sb, const char *text);
void sbPushStringInvisibleN(StringBuilder *sb, const char *text, usize n);
void sbPushChar(StringBuilder *string, char c);
void sbPushCharN(StringBuilder *string, char c, usize n);
char *stringDuplicate(const char *string);
char *stringDuplicateN(const char *string, usize n);

StringView stringViewFrom(const char *str, usize pos, usize length);

#endif
