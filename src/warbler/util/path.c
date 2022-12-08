#include <warbler/util/path.h>
#include <warbler/util/primitives.h>
#include <warbler/util/string.h>
#include <warbler/util/memory.h>
#include <warbler/util/print.h>

#include <assert.h>
#include <string.h>

static usize pathCopy(char *buffer, const char *path)
{
	usize len = 0;

	for (const char *iter = path; *iter; ++iter)
	{
		if (*iter == '\\' || *iter == '/')
		{
			buffer[len++] = '/';

			while (iter[1] == '\\' || iter[1] == '/')
				++iter;
			
			continue;
		}

		buffer[len++] = *iter;
	}

	return len;
}

char *pathJoin(const char *left, const char *right)
{
	// TODO: Optimize
	assert(left);

	if (!right)
		return pathDuplicate(left);

	usize leftLen = strlen(left);
	usize rightLen = strlen(right);
	char *buffer = allocate(leftLen + rightLen + 2);
	usize len = pathCopy(buffer, left);

	if (buffer[len - 1] != '/')
		buffer[len++] = '/';

	len += pathCopy(buffer + len, right);

	buffer[len] = '\0';
	
	return buffer;
}

char *pathGetRelative(const char *base, const char *path)
{
	usize offset = strlen(base);

	if (path[offset] == '/')
		offset += 1;

	return stringDuplicate(path + offset);
}

char *pathDuplicate(const char *path)
{
	usize pathLen = strlen(path);
	char *buffer = allocate(pathLen + 1);
	usize len = pathCopy(buffer, path);
	
	buffer[len] = '\0';

	return buffer;
}

char *pathGetFilename(const char *path)
{
	const char *end = path;

	while (*end)
		++end;

	if (end - path == 0)
		return NULL;

	while (end[-1] == '/')
		end -= 1;

	const char *begin = end;

	while (begin > path)
	{
		if (begin[-1] == '/')
			break;

		--begin;
	}

	char *fileName = stringDuplicateN(begin, end - begin);

	return fileName;
}
