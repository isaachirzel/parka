#ifndef WARBLER_FILE_H
#define WARBLER_FILE_H


#include <warbler/util/primitives.h>
#include <warbler/util/string.h>

#include <assert.h>

typedef struct File
{
	char *path;
	char *src;
	usize length;
	usize *lineLengths;
	usize lineCount;
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