#include <warbler/preprocessor.hpp>

// standard library
#include <cstddef>

namespace warbler
{
	char *read_text_literal(char *pos)
	{
		char terminal = pos[0];
		++pos;

		while (1)
		{
			if (!pos[0])
				return pos;

			if (pos[0] == terminal && pos[-1] != '\\')
				return pos + 1;

			++pos;
		}
	}

	struct BlockCommentResult
	{
		char *end_of_comment;
		size_t new_line_count;
	};

	char *read_line_comment(char *pos)
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

	BlockCommentResult read_block_comment(char *pos)
	{
		size_t new_line_count = 0;
		
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

		return { pos, new_line_count};
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

						pos = res.end_of_comment - 1;
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
				{
					char *end_of_text = read_text_literal(pos);

					size_t text_length = end_of_text - pos;
					for (size_t i = 0; i < text_length; ++i)
						src[oi++] = pos[i];

					pos = end_of_text - 1;
					break;
				}

				default:
					src[oi++] = *pos;
					break;
			}
		}

		src[oi] = 0;
	}
}

