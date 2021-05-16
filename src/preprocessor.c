#include <grackle/preprocessor.h>

#include <stddef.h>

void preprocess(char *src)
{
	// stripping comments
	size_t oi = 0;
	for (char *pos = src; *pos; ++pos)
	{
		// line comment
		if (pos[0] == '/' && pos[1] == '/')
		{
			// go till new line
			pos += 2;
			while (*pos)
			{
				if (*pos == '\n') break;
				pos += 1;
			}
		}
		else if (pos[0] == '/' && pos[1] == '*')
		{
			// replacing first character with space so there aren't unintended
			// syntactic consequences
			src[oi++] = ' ';
			// skip first 2 characters of block
			pos += 2;
			while (*pos)
			{
				if (pos[0] == '\n')
				{
					src[oi++] = '\n';
				}
				else if (pos[0] == '*' && pos[1] == '/')
				{
					// skip last two characters
					pos += 2;
					break;
				}
				pos += 1;
			}
		}
		// store head character in new position
		src[oi++] = *pos;
	}
	src[oi] = 0;
	// stripping comments
}
