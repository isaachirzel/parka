#include <warbler/snippet.h>
#include <warbler/util/memory.h>

Snippet getSnippet(const File *file, usize pos, usize length)
{
	assert(pos + length < file->length);

	Snippet snippet =
	{
		.file = file,
		.line = fileGetLine(file, pos),
		.col = fileGetCol(file, pos)
	};

	usize startOfLine = pos - snippet.col;
	usize end = pos + length;
	usize currentLine = snippet.line;

	for (pos; pos < end; ++pos)
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
