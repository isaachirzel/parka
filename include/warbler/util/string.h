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
void sbClear(StringBuilder *sb);
void sbDestroy(StringBuilder *sb);
void sbReserve(StringBuilder *sb, usize capacity);
void sbConcat(StringBuilder *sb, const StringBuilder *text);
const char *sbPushLine(StringBuilder *sb, const char *text);
void sbPushString(StringBuilder *sb, const char *text);
void sbPushStringN(StringBuilder *sb, const char *text, usize n);
void sbPushStringInvisible(StringBuilder *sb, const char *text);
void sbPushStringInvisibleN(StringBuilder *sb, const char *text, usize n);
void sbPushChar(StringBuilder *sb, char c);
void sbPushCharN(StringBuilder *sb, char c, usize n);
char *stringDuplicate(const char *sb);
char *stringDuplicateN(const char *sb, usize n);
usize stringFindOccurrence(const char *text, const char *token);

StringView stringViewFrom(const char *str, usize pos, usize length);

#endif
