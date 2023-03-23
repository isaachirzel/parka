#ifndef PARKA_DIRECTORY_HPP
#define PARKA_DIRECTORY_HPP

#include "parka/util/file.hpp"

struct Directory;

struct DirectoryEntry
{
    union
    {
        File file;
        struct Directory *directory;
    };
    bool isDirectory;
};

class Directory
{
    char *name;
    char *path;
    DirectoryEntry *entries;
    usize entryCount;

public:

    
};

Directory directoryRead(const char *path);
void directoryAddFile(Directory *dir, File *file);
void directoryList(const Directory *dir);
void directoryDestroy(Directory *dir);
void directoryEntryDestroy(DirectoryEntry *entry);

#endif
