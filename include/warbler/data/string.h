#ifndef WARBLER_STRING_H
#define WARBLER_STRING_H

#include <stdio.h>

typedef struct String
{
	const char *start;
	size_t len;
} String;

void printString(const String *str);
void printlnString(const String *str);
char *duplicateString(const String *str);

#endif
