#ifndef PARKA_UTIL_FILE_HPP
#define PARKA_UTIL_FILE_HPP

#include "parka/util/Array.hpp"
#include "parka/util/Primitives.hpp"
#include "parka/util/String.hpp"
#include "parka/file/FilePosition.hpp"

#include <cassert>

namespace parka
{
	enum class FileType
	{
		Regular,
		Source,
		Json
	};

	class File
	{
		String _path;
		String _text;
		Array<usize> _lineLengths;
		FileType _type;

		File(String&& path, String&& text) :
		_path(std::move(path)),
		_text(std::move(text)),
		_lineLengths(getLineLengths(_text)),
		_type(getType(_path))
		{}

		static FileType getType(const String& filepath);
		static Array<usize> getLineLengths(const String& text);

	public:

		File(File&&) = default;
		File(const File&) = delete;
		~File() = default;

		static File read(const String& filepath, usize pathOffset = 0);
		static File read(const String& directoryPath, const String& filename);
		static File from(const String& name, const String& text);

		usize getLine(usize pos) const;
		usize getCol(usize pos) const;
		bool hasExtension(const char *extension) const;
		const char& operator[](usize index) const { assert(index <= _text.length()); return _text[index]; }
		FilePosition getPosition(usize pos) const;

		const auto& path() const { return _path; }
		const auto& text() const { return _text; }
		const auto& lineLengths() const { return _lineLengths; }
		const auto& type() const { return _type; }
		auto lineCount() const { return _lineLengths.length(); }
		auto length() const { return _text.length(); }
	};
}

#endif
