#include "parka/util/path.h"
#include "parka/util/primitives.h"
#include "parka/util/string.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

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

void pathGetCurrentWorkingDirectory(char *buffer)
{
	// TODO: Make OS agnostic

	getcwd(buffer, PATH_MAX);
}

void pathGetExecutableDirectory(char *buffer)
{
	// TODO: Make OS agnostic
	
	const char *procPath = "/proc/self/exe";
	// FreeBSD: /proc/curproc/file
	// Solaris: /proc/self/path/a.out
	// Windows: GetModuleFileName(NULL, buffer, PATH_MAX)

	usize length = readlink(procPath, buffer, PATH_MAX);

	buffer[length] = '\0';
}
