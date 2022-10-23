#ifndef WARBLER_FILE_TREE_H
#define WARBLER_FILE_TREE_H

#include <warbler/file.h>

typedef struct Directory
{
    char *path;
    File *files;
    usize fileCount;
} Directory;

Directory directoryFrom(const char *path, File *file);
Directory *readDirectory(const char *path);

void addDirectoryFile(Directory *dir, File *file);

#endif
