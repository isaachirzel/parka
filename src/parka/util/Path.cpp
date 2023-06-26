#include "parka/util/Path.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"

#include <cstdlib>
#include <cstring>
#include <filesystem>

namespace parka::path
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
