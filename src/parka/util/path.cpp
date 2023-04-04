#include "parka/util/path.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

#include "parka/util/print.hpp"

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <filesystem>

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
		auto i = path.size();

		while (i > 0)
		{
			i -= 1;

			if (path[i] == '/')
			{
				i += 1;
				break;
			}
		}

		auto filename = path.substr(i);

		return filename;
	}

	String toAbsolute(const String &path)
	{
		auto absolute = std::filesystem::absolute(path);

		return absolute.string();
	}

	usize getParentFolderPathOffset(const String& path)
	{
		auto i = path.size();

		while (i > 0)
		{
			i -= 1;

			if (path[i] == '/')
			{
				break;
			}
		}

		return i;
	}
}
