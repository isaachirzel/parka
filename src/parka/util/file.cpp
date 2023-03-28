#include "parka/util/file.hpp"

#include "parka/util/print.hpp"
#include "parka/util/path.hpp"
#include "parka/util/string.hpp"

#include <cstdio>
#include <cassert>
#include <cstring>

String readFileText(const String& filepath)
{
	FILE *file = fopen(filepath.c_str(), "r");
	
	if (!file)
		exitWithError("Failed to open file '$'.", filepath.c_str());

	if (fseek(file, 0, SEEK_END))
		exitWithError("Failed to seek end of file '$'.", filepath.c_str());

	long size = ftell(file);

	if (size == -1)
		exitWithError("File '$' is invalid size.", filepath.c_str());

	if (fseek(file, 0, SEEK_SET))
		exitWithError("Failed to seek beginning of file '$'.", filepath.c_str());

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
		printError("Failed to open file '$' for writing.", filepath);
		return false;
	}

	usize bytesWritten = fwrite(content.c_str(), sizeof(char), content.length(), file);

	fclose(file);

	if (bytesWritten != content.length())
	{
		printError("Failed to write content to file '$'.", filepath);
		return false;
	}

	return true;
}

Array<usize> File::getLineLengths(const String& text)
{
	auto lengths = Array<usize>(text.length() / 80);
	usize lastStartOfLine = 0;
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

	const char *lastPoint = NULL;
	const char *end = &filepath[0];

	while (*end)
	{
		if (*end == '.')
			lastPoint = end;

		end += 1;
	}

	if (lastPoint == NULL || end - lastPoint == 1)
		return FILE_REGULAR;
	
	const char *extension = lastPoint + 1;

	if (!strcmp(extension, "pk"))
		return FILE_SOURCE;

	if (!strcmp(extension, "json"))
		return FILE_JSON;

	return FILE_REGULAR;
}

File File::read(const String& directoryPath, const String& filename)
{
	// TODO: Optimize
	auto path = path::join(directoryPath, filename);
	auto text = readFileText(path);
	auto file = File(std::move(path), std::move(text));

	return file;
}

File File::read(const String& path)
{
	auto text = readFileText(path);
	auto lineLengths = getLineLengths(text);
	auto file = File(String(path), std::move(text));

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

FilePosition File::getPosition(usize pos) const
{
	assert(pos <= _text.length());
	
	usize line = 1;
	usize col = 1;

	usize filePos = 0;

	for (auto length : _lineLengths)
	{
		if (filePos + length > pos)
			break;

		filePos += length + 1;
		line += 1;
	}

	col = pos - filePos + 1;

	return { line, col };
}
