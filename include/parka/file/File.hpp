#ifndef PARKA_FILE_FILE_HPP
#define PARKA_FILE_FILE_HPP

#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	enum class FileType: u8
	{
		Regular,
		Source,
		Json
	};

	class File
	{
		String _path;
		String _text;
		FileType _type;

		File(String&& path, String&& text);

		static FileType getType(const String& filepath);

	public:

		File(File&&) = default;
		File(const File&) = delete;

		static File read(const String& filepath, usize pathOffset = 0);
		static File read(const String& directoryPath, const String& filename);
		static File from(const String& name, const String& text);

		bool hasExtension(const char *extension) const;
		String substr(const usize index, const usize length) const;
		const char& operator[](usize index) const { assert(index <= _text.length()); return _text[index]; }

		const auto& path() const { return _path; }
		const auto& text() const { return _text; }
		const auto& type() const { return _type; }
		auto length() const { return _text.length(); }
	};
}

#endif
