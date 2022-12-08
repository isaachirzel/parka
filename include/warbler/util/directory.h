#ifndef WARBLER_FILE_TREE_H
#define WARBLER_FILE_TREE_H

#include <warbler/util/file.h>

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
    char *name;
    char *path;
    Entry *entries;
    usize entryCount;
} Directory;

Directory directoryRead(const char *path);
void directoryAddFile(Directory *dir, File *file);
void directoryList(const Directory *dir);
void entryDestroy(Entry *entry);
void directoryDestroy(Directory *dir);

#endif
