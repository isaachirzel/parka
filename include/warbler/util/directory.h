#ifndef WARBLER_DIRECTORY_H
#define WARBLER_DIRECTORY_H

#include "warbler/util/file.h"

struct Directory;

typedef struct DirectoryEntry
{
    union
    {
        File file;
        struct Directory *directory;
    };
    bool isDirectory;
} DirectoryEntry;

typedef struct Directory
{
    char *name;
    char *path;
    DirectoryEntry *entries;
    usize entryCount;
} Directory;

Directory directoryRead(const char *path);
void directoryAddFile(Directory *dir, File *file);
void directoryList(const Directory *dir);
void directoryDestroy(Directory *dir);
void directoryEntryDestroy(DirectoryEntry *entry);

#endif
