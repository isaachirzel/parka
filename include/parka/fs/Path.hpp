#ifndef PARKA_FS_PATH_HPP
#define PARKA_FS_PATH_HPP

#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"
#include "parka/util/StringView.hpp"

#include <filesystem>

namespace parka::fs
{
	class Path
	{
		String _text;
		u16 _projectOffset;
		u16 _nameOffset;
		u16 _extensionOffset;

	public:

		Path();
		Path(const char* text);
		Path(const String& text);
		Path(const std::filesystem::path& path);
		Path(Path&&) = default;
		Path(const Path&) = default;
		Path& operator=(Path&&) = default;
		Path& operator=(const Path&) = default;

		bool hasExtension(const char *extension) const;
		String getFilename() const;

		const auto& text() const { return _text; }
		bool empty() const { return _text.empty(); }
		StringView extension() const;

		Path operator/(const char *other) const;
		Path& operator/=(const char *other);

		friend std::ostream& operator<<(std::ostream& out, const Path& path);
	};
}

#endif
