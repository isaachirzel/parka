#include <warbler/directory.h>
#include <string.h>
#include <warbler/util/print.h>
#include <warbler/util/memory.h>
#include <warbler/util/string.h>
#include <warbler/util/path.h>
#include <stdio.h>

#if defined (_WIN32) || defined(_WIN64)

#else

#include <dirent.h>

static Directory readSubdirectory(const char *base, const char *name)
{
	Directory directory =
	{
		.path = pathJoin(base, name)
	};

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
			File file = fileReadRelative(directory.path, entry->d_name);
			usize index = directory.entryCount;

			resizeArray(directory.entries, ++directory.entryCount);

			directory.entries[index] = (Entry) { .file = file };
		}
		else if (entry->d_type == DT_DIR)
		{
			Directory subDirectory = readSubdirectory(directory.path, entry->d_name);

			resizeArray(directory.entries, ++directory.entryCount);

			Entry *dirEntry = &directory.entries[directory.entryCount - 1];

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
		const Entry *entry = &dir->entries[i];

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

Directory *directoryGetSrcDir(Directory *projectDirectory)
{
	for (usize i = 0; i < projectDirectory->entryCount; ++i)
	{
		Entry *entry = &projectDirectory->entries[i];

		if (!entry->isDirectory)
			continue;

		Directory *dir = entry->directory;
		const char *dirname = pathGetFilenameComponent(dir->path);

		if (!strcmp(dirname, "src"))
			return dir;
	}

	return NULL;
}

#endif