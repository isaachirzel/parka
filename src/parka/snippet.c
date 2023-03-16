#include "parka/snippet.h"
#include "parka/util/memory.h"
#include "parka/util/string.h"

Snippet getSnippet(const File *file, const usize startPos, usize length)
{
	Snippet snippet =
	{
		.filename = stringDuplicate(file->path),
		.line = fileGetLine(file, startPos),
		.col = fileGetCol(file, startPos)
	};

	usize startOfLine = startPos - snippet.col;
	usize end = startPos + length;
	usize currentLine = snippet.line;
	usize pos = startPos;

	for (; pos < end; ++pos)
	{
		char character = fileGetChar(file, pos);

		if (character == '\n')
		{
			StringView substr = stringViewFrom(file->src, startOfLine, pos - startOfLine);

			resizeArray(snippet.lines, ++snippet.lineCount);
			snippet.lines[snippet.lineCount - 1] = substr;

			startOfLine = pos + 1;
			currentLine += 1;
		}
	}

	snippet.endCol = end - startOfLine - 1;

	while (true)
	{
		char character = fileGetChar(file, pos);

		if (character == '\0' || character == '\n')
			break;

		pos += 1;
	}

	StringView line = stringViewFrom(file->src, startOfLine, pos - startOfLine);

	resizeArray(snippet.lines, ++snippet.lineCount);
	snippet.lines[snippet.lineCount - 1] = line;

	return snippet;
}

Snippet snippetFromToken(const Token *token)
{
	return getSnippet(token->file, token->pos, token->length);
}

Snippet snippetFromTokens(const Token *first, const Token *last)
{
	return getSnippet(first->file, first->pos, last->pos + last->length - first->pos);
}
