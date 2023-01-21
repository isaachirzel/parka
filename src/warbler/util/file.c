#include <warbler/util/file.h>
#include <warbler/util/memory.h>
#include <warbler/util/print.h>
#include <warbler/util/path.h>

#include <stdio.h>
#include <assert.h>

static bool readStreamText(StringBuilder *out, FILE *file)
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

	*out = (StringBuilder) { buffer, bytesRead, bytesRead };
	return true;
}

static StringBuilder readFileText(const char *filepath)
{
	FILE *file = fopen(filepath, "r");
	
	if (!file)
		exitWithErrorFmt("Failed to open file '%s'.", filepath);

	StringBuilder out;

	if (!readStreamText(&out, file))
		exitWithErrorFmt("Failed to read file '%s'.", filepath);

	fclose(file);

	return out;
}

bool writeFileText(const char *filepath, const StringBuilder *content)
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

static void addLine(File *file, usize length)
{
	resizeArray(file->lineLengths, ++file->lineCount);
	
	file->lineLengths[file->lineCount - 1] = length;
}

static void getLineLengths(File *file)
{
	usize lastStartOfLine = 0;

	for (usize i = 0; i < file->length; ++i)
	{
		char character = file->src[i];

		if (character == '\n')
		{
			usize length = (i + 1) - lastStartOfLine;

			addLine(file, length);

			lastStartOfLine = i + 1;
		}
	}

	usize length = (file->length + 1) - lastStartOfLine;

	addLine(file, length);
}

File fileReadRelative(const char *directory, const char *filename)
{
	// TODO: Optimize
	char *path = pathJoin(directory, filename);
	StringBuilder text = readFileText(path);
	File file =
	{
		.path = path,
		.src = text.data,
		.length = text.length
	};

	getLineLengths(&file);

	return file;
}

File fileRead(const char *path)
{
	StringBuilder text = readFileText(path);
	File file =
	{
		.path = pathDuplicate(path),
		.src = text.data,
		.length = text.length
	};

	getLineLengths(&file);

	return file;
}

File fileFrom(const char *name, const char *text)
{
	StringBuilder str = sbFrom(text);
	File file =
	{
		.path = stringDuplicate(name),
		.src = str.data,
		.length = str.length
	};

	getLineLengths(&file);

	return file;
}

void fileDestroy(File *file)
{
	deallocate(file->path);
	deallocate(file->src);
	deallocate(file->lineLengths);
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

char fileGetChar(const File *file, usize pos)
{
	assert(file);
	assert(pos <= file->length);

	return file->src[pos];
}

char *fileGetText(const File *file, usize pos, usize length)
{
	assert(file);
	assert(pos + length <= file->length);

	char *text = allocate(length + 1);
	const usize end = pos + length;
	usize textIndex = 0;

	for (usize fileIndex = pos; fileIndex < end; ++fileIndex)
		text[textIndex++] = file->src[fileIndex];

	text[textIndex] = 0;

	return text;
}

void fileCopyText(const File *file, char *out, usize pos, usize length)
{
	assert(pos + length < file->length);

	usize end = pos + length;
	usize textIndex = 0;

	for (usize i = pos; i < end; ++i)
		out[textIndex] = file->src[i];
}

FilePosition fileGetPosition(const File *file, usize pos)
{
	assert(pos < file->length);

	FilePosition position =
	{
		.line = 1,
		.col = 1
	};
	usize filePos = 0;

	for (usize i = 0; i < file->lineCount; ++i)
	{
		if (filePos + file->lineLengths[i] > pos)
		{
			position.line = i + 1;
			position.col = pos - filePos + 1;

			break;
		}

		filePos += file->lineLengths[i];
	}

	return position;
}
