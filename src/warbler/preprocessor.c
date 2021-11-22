// header
#include <warbler/preprocessor.h>

// standard library
#include <stddef.h>

const char *read_text_literal(const char *pos)
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

struct BlockCommentResult
{
	const char *end_of_comment;
	unsigned new_line_count;
};

const char *read_line_comment(const char *pos)
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
	auto new_line_count = 0u;
	
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

	return BlockCommentResult { pos, new_line_count };
}

std::string preprocess(const std::string& src)
{
	// stripping comments
	std::string out(src.size(), 0);

	size_t oi = 0;

	auto is_in_text = false;

	for (auto pos = src.c_str(); *pos; ++pos)
	{
		switch (*pos)
		{
			case '/':
				if (pos[1] == '/')
				{
					pos = read_line_comment(pos);
					out[oi++] = '\n';
				}
				else if (pos[1] == '*')
				{
					auto res = read_block_comment(pos);

					pos = res.end_of_comment;
					out[oi++] = ' ';

					for (unsigned i = 0; i < res.new_line_count; ++i)
						out[oi++] = '\n';
				}
				break;

			case '\'':
			case '\"':
				auto end_of_string = read_text_literal(pos);

				for (size_t i = 0; i < end_of_string - pos; ++i)
					out[oi++] = pos[i];

				pos = end_of_string;
				break;

			default:
				out[oi++] = *pos;
				break;
		}

		if (*pos == '/')
		{
			// line comment
			if (pos[1] == '/')
			{
			}
			// block comment
			else if (pos[1] == '*')
			{
				// replacing first character with space so there aren't unintended
				// syntactic consequences
				out[oi++] = ' ';
				// skip first 2 characters of block
				pos += 2;
				while (*pos)
				{
					if (pos[0] == '\n')
					{
						out[oi++] = '\n';
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
		}

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
			
		}
		// store head character in new position
		out[oi++] = *pos;
	}

	out.resize(oi);

	return out;
}
