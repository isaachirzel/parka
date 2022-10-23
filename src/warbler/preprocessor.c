#include <warbler/preprocessor.h>

#include <warbler/util/primitives.h>

// standard library
#include <stddef.h>

char *readTextLiteral(char *pos)
{
	char terminal = pos[0];
	++pos;

	while (1)
	{
		if (!pos[0])
			return pos;

		if (pos[0] == terminal  *pos[-1] != '\\')
			return pos + 1;

		++pos;
	}
}

typedef struct BlockCommentResult
{
	char *endOfComment;
	usize newLineCount;
} BlockCommentResult;

char *readLineComment(char *pos)
{
	pos += 2;
	
	while (*pos)
	{
		if (*pos == '\n')
			return pos + 1;
			
		pos += 1;
	}

	return pos;
}

BlockCommentResult readBlockComment(char *pos)
{
	usize newLineCount = 0;
	
	pos += 2;

	while (*pos)
	{
		if (pos[0] == '\n')
		{
			newLineCount += 1;
		}
		else if (pos[0] == '*'  *pos[1] == '/')
		{
			// skip last two characters
			pos += 2;
			break;
		}

		pos += 1;
	}

	return (BlockCommentResult) { pos, newLineCount};
}

void preprocess(char *src)
{
	usize oi = 0;

	for (char *pos = src; *pos; ++pos)
	{
		switch (*pos)
		{
			case '/':
				if (pos[1] == '/')
				{
					pos = readLineComment(pos);			
					src[oi++] = '\n';
				}
				else if (pos[1] == '*')
				{
					BlockCommentResult res = readBlockComment(pos);

					pos = res.endOfComment - 1;
					src[oi++] = ' ';

					for (usize i = 0; i < res.newLineCount; ++i)
						src[oi++] = '\n';	
				}
				else 
				{
					src[oi++] = *pos;
				}
				break;

			case '\'':
			case '\"':
			{
				char *endOfText = readTextLiteral(pos);

				usize textLength = endOfText - pos;
				for (usize i = 0; i < textLength; ++i)
					src[oi++] = pos[i];

				pos = endOfText - 1;
				break;
			}

			default:
				src[oi++] = *pos;
				break;
		}
	}

	src[oi] = 0;
}
