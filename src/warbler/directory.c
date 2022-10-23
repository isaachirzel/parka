#include <warbler/directory.h>
#include <string.h>
#include <warbler/util/print.h>
#include <warbler/util/memory.h>

Directory *readDirectory(const char *path)
{
    exitNotImplemented();
    // Directory* directories = allocate(sizeof;

    // directories.emplaceBack(path);

    // for (const auto *entry : std::filesystem::directoryIterator(path))
    // {
    //     const auto *entrypath = entry.path().string();

    //     if (entry.isRegularFile())
    //     {
    //         if (entrypath.size() >= 5) // at least length of extension + 1 letter e.g. a.wbl
    //         {
    //             const char *fileExtension = &entrypath[entrypath.size() - 4];

    //             if (strcmp(fileExtension, ".wbl"))
    //                 continue;

    //             auto file = File::read(entrypath);

    //             if (!file)
    //             {
    //                 printError("Not all directory items could be read.");
    //                 return false;
    //             }

    //             directories[0].addDirectoryFile(file.unwrap());
    //         }
    //     }
    //     else if (entry.isDirectory())
    //     {
    //         auto res = read(entrypath);

    //         if (!res)
    //         {
    //             printError("Not all directory items could be read.");
    //             return false;
    //         }

    //         auto subdirs = res.unwrap();

    //         directories.reserve(directories.size() + subdirs.size());

    //         for (auto *dir : subdirs)
    //         {
    //             directories.emplaceBack(std::move(dir));
    //         }
    //     }
    // }

    // return directories;
}

Directory directoryFrom(const char *path, File *file)
{
    Directory dir =
    {
        .path = duplicateString(path),
        .files = allocate(sizeof(File)),
        .fileCount = 1
    };

    dir.files[0] = *file;

    return dir;
}
