#ifndef PARKA_UTIL_STRING_HPP
#define PARKA_UTIL_STRING_HPP

#include "parka/util/primitives.hpp"
#include "parka/util/arena.hpp"
#include <string>

using String = std::string;

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
StringBuilder sbFrom(const char *text);
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

char *stringDuplicate(const char *string);
char *stringDuplicateN(const char *string, usize n);
usize stringFindOccurrence(const char *text, const char *token);

StringView stringViewFrom(const char *string, usize pos, usize length);

#endif
