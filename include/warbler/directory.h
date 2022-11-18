#ifndef WARBLER_FILE_TREE_H
#define WARBLER_FILE_TREE_H

#include <warbler/file.h>

struct Directory;

typedef struct Entry
{
    union
    {
        File file;
        struct Directory *directory;
    };
    bool isDirectory;
} Entry;

typedef struct Directory
{
    char *path;
    Entry *entries;
    usize entryCount;
} Directory;

Directory directoryRead(const char *path);
Directory *directoryGetSrcDir(Directory *projectDirectory);
void directoryAddFile(Directory *dir, File *file);
void directoryList(const Directory *dir);

#endif
