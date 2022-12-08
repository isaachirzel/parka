#ifndef WARBLER_SNIPPET_H
#define WARBLER_SNIPPET_H

#include <warbler/util/file.h>
#include <warbler/token.h>

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
