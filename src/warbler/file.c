#include <warbler/file.h>
#include <warbler/util/memory.h>
#include <warbler/util/print.h>

#include <stdio.h>
#include <assert.h>

static bool readStreamText(String *out, FILE *file)
{
	if (fseek(file, 0, SEEK_END))
		return false;

	long size = ftell(file);

	if (size == -1)
		return false;

	if (fseek(file, 0, SEEK_SET))
		return false;

	char *buffer = allocate(size + 1);
	usize bytesRead = fread(buffer, sizeof(char), size, file);

	buffer[bytesRead] = '\0';

	*out = (String) { buffer, bytesRead, bytesRead };
	return true;
}

static String readFileText(const char *filepath)
{
	FILE *file = fopen(filepath, "r");
	
	if (!file)
	{
		exitWithError("Failed to open file '%s'.", filepath);
	}

	String out;

	if (!readStreamText(&out, file))
	{
		exitWithError("Failed to read file '%s'.", filepath);
	}

	fclose(file);

	if (out.length == 0)
	{
		exitWithError("File '%s' was empty.", filepath);
	}

	return out;
}

bool writeFileText(const char *filepath, const String *content)
{
	FILE *file = fopen(filepath, "w");

	if (!file)
	{
		printError("Failed to open file '%s' for writing.", filepath);
		return false;
	}

	usize bytesWritten = fwrite(content->data, sizeof(char), content->length, file);

	fclose(file);

	if (bytesWritten != content->length)
	{
		printError("Failed to write content to file '%s'.", filepath);
		return false;
	}

	return true;
}

static void getLineLengths(File *file)
{
	usize estimatedLineCount = file->length / 80 + 1;
	usize lastStartOfLine = 0;

	for (usize i = 0; i < file->length; ++i)
	{
		if (file->src[i] == '\n')
		{
			usize lineLength = i - lastStartOfLine + 1;

			file->lineCount += 1;
			file->lineLengths = resizeArray(file->lineLengths, file->lineCount);
			file->lineLengths[file->lineCount - 1] = lineLength;

			lastStartOfLine = i + 1;
		}
	}
}

File fileRead(const char *filepath)
{
	String text = readFileText(filepath);

	File file =
	{
		.name = duplicateString(filepath),
		.src = text.data,
		.length = text.length
	};

	getLineLengths(&file);

	return file;
}

struct File fileFrom(const char *name, const char *text)
{
	String str = stringFrom(text);

	File file =
	{
		.name = duplicateString(name),
		.src = str.data,
		.length = str.length
	};

	getLineLengths(&file);

	return file;
}

usize fileGetLine(const File *file, usize pos)
{
	usize line = 0;

	for (usize i = 0; i < file->lineCount; ++i)
	{
		usize length = file->lineLengths[i];

		if (pos >= length)
		{
			line += 1;
			pos -= length;
		}
	}

	return line;
}

usize fileGetCol(const File *file, usize startPos)
{
	usize pos = startPos;

	while (true)
	{
		if (pos == 0 || file->src[pos - 1] == '\n')
			break;

		pos -= 1;
	}

	return startPos - pos;
}

StringView getFileText(const File *file, usize pos, usize length)
{		
	assert(pos + length < file->length);

	return (StringView) { file->src + pos, length };
}
