#include "parka/util/path.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

#include "parka/util/print.hpp"

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <filesystem>
// #include <unistd>

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

	String getRelativePath(const String& base, const String& path)
	{
		usize offset = base.length();

		if (path[offset] == '/')
			offset += 1;

		auto str = String(path.c_str() + offset);

		return str;
	}

	String getFilename(const String& path)
	{
		const char *end = path.c_str();

		while (*end)
			++end;

		if (end - path.c_str() == 0)
			return "";

		while (end[-1] == '/')
			end -= 1;

		const char *begin = end;

		while (begin > path)
		{
			if (begin[-1] == '/')
				break;

			--begin;
		}

		auto filename = String(begin, end - begin);

		return filename;
	}

	// void pathGetExecutableDirectory(char *buffer)
	// {
	// 	// TODO: Make OS agnostic
		
	// 	const char *procPath = "/proc/self/exe";
	// 	// FreeBSD: /proc/curproc/file
	// 	// Solaris: /proc/self/path/a.out
	// 	// Windows: GetModuleFileName(NULL, buffer, PATH_MAX)

	// 	usize length = readlink(procPath, buffer, PATH_MAX);

	// 	buffer[length] = '\0';
	// }

	String toAbsolute(const String &path)
	{
		auto absolute = std::filesystem::absolute(path);

		return absolute.string();
	}
}


