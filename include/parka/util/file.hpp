#ifndef PARKA_FILE_HPP
#define PARKA_FILE_HPP

#include "parka/util/array.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

#include <assert.h>

enum FileType
{
	FILE_REGULAR,
	FILE_SOURCE,
	FILE_JSON
};

struct FilePosition
{
	usize line;
	usize col;
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
	_type(getType(_text))
	{}

	static FileType getType(const String& filepath);
	static Array<usize> getLineLengths(const String& text);

public:

	File(File&&) = default;
	File(const File&) = delete;
	~File() = default;

	static File read(const String& filepath);
	static File read(const String& directoryPath, const String& filename);
	static File from(const String& name, const String& text);

	usize getLine(usize pos) const;
	usize getCol(usize pos) const;
	bool hasExtension(const char *extension) const;
	char operator[](usize index) const;
	FilePosition getPosition(usize pos) const;

	const auto& path() const { return _path; }
	const auto& text() const { return _text; }
	const auto& lineLengths() const { return _lineLengths; }
	const auto& type() const { return _type; }
};

#endif
