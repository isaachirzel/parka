#ifndef PARKA_FILE_H
#define PARKA_FILE_H

#include "parka/util/primitives.h"
#include "parka/util/string.h"

#include <assert.h>

typedef enum FileType
{
	FILE_REGULAR,
	FILE_SOURCE,
	FILE_JSON
} FileType;

typedef struct File
{
	char *path;
	char *src;
	usize length;
	usize *lineLengths;
	usize lineCount;
	FileType type;
} File;

typedef struct FilePosition
{
	usize line;
	usize col;
} FilePosition;

bool fileHasExtension(const File *file, const char *extension);
File fileReadRelative(const char *directory, const char *filename);
void fileDestroy(File *file);
File fileRead(const char *path);
File fileFrom(const char *name, const char *text);
usize fileGetLine(const File *file, usize pos);
usize fileGetCol(const File *file, usize pos);
char *fileGetText(const File *file, usize pos, usize length);
char fileGetChar(const File *file, usize index);
void fileCopyText(const File *file, char *out, usize pos, usize length);
FilePosition fileGetPosition(const File *file, usize pos);

#endif
