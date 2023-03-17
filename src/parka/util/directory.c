#include "parka/util/directory.h"
#include <string.h>
#include "parka/util/print.h"
#include "parka/util/memory.h"
#include "parka/util/string.h"
#include "parka/util/path.h"
#include <stdio.h>

#if defined (_WIN32) || defined(_WIN64)
#else
#include <dirent.h>
#endif

static Directory readSubdirectory(const char *base, const char *name)
{
	Directory directory =
	{
		.name = name ? stringDuplicate(name) : pathGetFilename(base),
		.path = pathJoin(base, name)
	};
	
	printFmt("Reading subdirectory: %s : %s", directory.path, directory.name);

	DIR *dir = opendir(directory.path);

	if (!dir)
		exitWithErrorFmt("Unable to open directory: %s", directory.path);

	while (true)
	{
		struct dirent *entry = readdir(dir);
		
		if (!entry)
			break;

		// Skip hidden files
		if (entry->d_name[0] == '.')
			continue;

		if (entry->d_type == DT_REG)
		{
			printFmt("Regular file: %s", entry->d_name);
			File file = fileReadRelative(directory.path, entry->d_name);
			usize index = directory.entryCount;

			resizeArray(directory.entries, ++directory.entryCount);

			directory.entries[index] = (DirectoryEntry)
			{
				.file = file
			};
		}
		else if (entry->d_type == DT_DIR)
		{
			Directory subDirectory = readSubdirectory(directory.path, entry->d_name);

			resizeArray(directory.entries, ++directory.entryCount);

			DirectoryEntry *dirEntry = &directory.entries[directory.entryCount - 1];

			dirEntry->isDirectory = true;

			*makeNew(dirEntry->directory) = subDirectory;
		}
	}

	closedir(dir);

	return directory;
}

Directory directoryRead(const char *path)
{
	return readSubdirectory(path, NULL);
}


static void printTabbed(const char *text, usize tabs)
{
	if (tabs > 0)
	{
		for (usize i = 0; i < tabs - 1; ++i)
			fputs("    ", stdout);

		fputs("  > ", stdout);
	}

	puts(text);
}

static void listSubdirectory(const Directory *dir, usize depth)
{
	printTabbed(dir->path, depth);

	for (usize i = 0; i < dir->entryCount; ++i)
	{
		const DirectoryEntry *entry = &dir->entries[i];

		if (entry->isDirectory)
		{
			listSubdirectory(entry->directory, depth + 1);
			continue;
		}

		printTabbed(entry->file.path, depth + 1);
	}
}

void directoryList(const Directory *dir)
{
	listSubdirectory(dir, 0);
}

void directoryEntryDestroy(DirectoryEntry *entry)
{
	if (entry->isDirectory)
	{
		directoryDestroy(entry->directory);
		return;
	}
	
	fileDestroy(&entry->file);
}

void directoryDestroy(Directory *dir)
{
	for (usize i = 0; i < dir->entryCount; ++i)
		directoryEntryDestroy(&dir->entries[i]);

	deallocate(dir->name);
	deallocate(dir->path);
	deallocate(dir->entries);
}
