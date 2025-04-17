#ifndef PARKA_FS_FILE_HPP
#define PARKA_FS_FILE_HPP

#include "parka/fs/Path.hpp"
#include "parka/fs/FileType.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"

#include <cassert>

namespace parka::fs
{
	class File
	{
		String _text;
		Path _path;
        u8 _projectOffset;
		FileType _type;
		

	private:

		File(String&& text, const Path& path, u8 projectOffset, FileType fileType);

		static FileType getFileType(const Path& filepath);

	public:

		File(File&&) = default;
		File(const File&) = delete;

		static File read(const Path& filepath, u16 relativePathOffset = 0);
		static File createTestMainSrcFile(const Path& directoryPath, u16 relativePathOffset, String&& text);

		const char& operator[](usize index) const { assert(index <= _text.length()); return _text[index]; }

		void write();
		String getRelativePath() const;

		const auto& text() const { return _text; }
		const auto& path() const { return _path; }
		const auto& type() const { return _type; }
		auto length() const { return _text.length(); }
	};
}

#endif
