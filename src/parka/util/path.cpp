#include "parka/util/path.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

#include "parka/util/print.hpp"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

namespace path
{
	String join(const String& a, const String& b)
	{
		if (a.empty())
			return b;

		if (b.empty())
			return a;

		if (a.back() == '/' || b.front() == '/')
			return a + b;

		return a + '/' + b;
	};
}

usize pathCopy(char *buffer, const char *path)
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

char *pathGetRelative(const char *base, const char *path)
{
	usize offset = strlen(base);

	if (path[offset] == '/')
		offset += 1;

	return stringDuplicate(path + offset);
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
