// header
#include <warbler/preprocessor.h>

// standard library
#include <stddef.h>

char *read_text_literal(const char *pos)
{
	const auto terminal = *pos;
	pos += 1;

	while (*pos)
	{
		if (*pos == terminal && pos[-1] != '\\')
			return pos + 1;

		pos += 1;
	}

	return pos;
}

typedef struct BlockCommentResult
{
	char *end_of_comment;
	size_t new_line_count;
}
BlockCommentResult;

char *read_line_comment(const char *pos)
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

BlockCommentResult read_block_comment(const char *pos)
{
	size_t new_line_count = 0u;
	
	pos += 2;

	while (*pos)
	{
		if (pos[0] == '\n')
		{
			new_line_count += 1;
		}
		else if (pos[0] == '*' && pos[1] == '/')
		{
			// skip last two characters
			pos += 2;
			break;
		}

		pos += 1;
	}

	return (BlockCommentResult) { pos, new_line_count };
}

void preprocess(char *src)
{
	size_t oi = 0;

	for (char *pos = src; *pos; ++pos)
	{
		switch (*pos)
		{
			case '/':
				if (pos[1] == '/')
				{
					pos = read_line_comment(pos);			
					src[oi++] = '\n';
				}
				else if (pos[1] == '*')
				{
					BlockCommentResult res = read_block_comment(pos);

					pos = res.end_of_comment;
					src[oi++] = ' ';

					for (size_t i = 0; i < res.new_line_count; ++i)
						src[oi++] = '\n';
				}
				else 
				{
					src[oi++] = *pos;
				}
				break;

			case '\'':
			case '\"':
				char *end_of_string = read_text_literal(pos);

				for (size_t i = 0; i < end_of_string - pos; ++i)
					src[oi++] = pos[i];

				pos = end_of_string;
				break;

			default:
				src[oi++] = *pos;
				break;
		}
	}
}
