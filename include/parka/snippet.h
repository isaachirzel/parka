#ifndef PARKA_SNIPPET_H
#define PARKA_SNIPPET_H

#include "parka/util/file.h"
#include "parka/token.h"

typedef struct Snippet
{
	char *filename;
	StringView* lines;
	usize lineCount;
	usize endCol;
	usize line;
	usize col;
} Snippet;

Snippet snippetFromFile(const File *file, usize pos, usize length);
Snippet snippetFromToken(const Token *token);
Snippet snippetFromTokens(const Token *left, const Token *right);
void freeSnippet(Snippet *snippet);

#endif
