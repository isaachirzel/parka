#include "parka/file/File.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/String.hpp"

#include <cassert>
#include <cstring>

namespace parka
{
	String readFileText(const String& filepath)
	{
		FILE *file = fopen(filepath.c_str(), "r");
		
		if (!file)
			log::fatal("Failed to open file '$'.", filepath.c_str());

		if (fseek(file, 0, SEEK_END))
			log::fatal("Failed to seek end of file '$'.", filepath.c_str());

		long size = ftell(file);

		if (size == -1)
			log::fatal("File '$' is invalid size.", filepath.c_str());

		if (fseek(file, 0, SEEK_SET))
			log::fatal("Failed to seek beginning of file '$'.", filepath.c_str());

		auto text = String();

		text.resize(size);

		usize bytesRead = fread(&text[0], sizeof(char), size, file);

		text.resize(bytesRead);

		fclose(file);

		return text;
	}

	bool writeFileText(const char *filepath, const String& content)
	{
		FILE *file = fopen(filepath, "w");

		if (!file)
		{
			log::error("Failed to open file '$' for writing.", filepath);
			return false;
		}

		usize bytesWritten = fwrite(content.c_str(), sizeof(char), content.length(), file);

		fclose(file);

		if (bytesWritten != content.length())
		{
			log::error("Failed to write content to file '$'.", filepath);
			return false;
		}

		return true;
	}

	Array<usize> File::getLineLengths(const String& text)
	{
		auto lengths = Array<usize>(text.length() / 80);
		usize length = 0;

		for (auto c : text)
		{
			if (c == '\n')
			{
				lengths.push(length);
				length = 0;
				continue;
			}

			length += 1;
		}

		lengths.push(length);

		return lengths;
	}

	FileType File::getType(const String& filepath)
	{
		// TODO: Optimize and safety
		assert(!filepath.empty() && "Empty filepath");

		const char *lastPoint = nullptr;
		const char *end = &filepath[0];

		while (*end)
		{
			if (*end == '.')
				lastPoint = end;

			end += 1;
		}

		if (lastPoint == nullptr || end - lastPoint == 1)
			return FileType::Regular;
		
		const char *extension = lastPoint + 1;

		if (!strcmp(extension, "pk"))
			return FileType::Source;

		if (!strcmp(extension, "json"))
			return FileType::Json;

		return FileType::Regular;
	}

	File File::read(const String& directoryPath, const String& filename)
	{
		// TODO: Optimize
		auto path = path::join(directoryPath, filename);
		auto text = readFileText(path);
		auto file = File(std::move(path), std::move(text));

		return file;
	}

	File File::read(const String& path, usize pathOffset)
	{
		auto text = readFileText(path);
		auto lineLengths = getLineLengths(text);
		auto file = File(path.substr(pathOffset), std::move(text));

		return file;
	}

	File File::from(const String& name, const String& text)
	{
		auto file = File(String(name), String(text));

		return file;
	}

	usize File::getLine(usize pos) const
	{
		assert(pos < _text.length());

		usize line = 0;

		for (auto length : _lineLengths)
		{
			if (pos >= length)
			{
				line += 1;
				pos -= length;
			}
		}

		return line;
	}

	usize File::getCol(usize startPos) const
	{
		assert(startPos < _text.length());

		usize pos = startPos;

		while (true)
		{
			if (pos == 0 || _text[pos - 1] == '\n')
				break;

			pos -= 1;
		}

		return startPos - pos;
	}

	String File::substr(const usize index, const usize length) const
	{
		assert(index < _text.length());
		assert(index + length < _text.length());

		return _text.substr(index, length);
	}
}
