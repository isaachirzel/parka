#include <warbler/directory.hpp>

#include <filesystem>
#include <cstring>
#include <warbler/util/print.hpp>

namespace warbler
{
    Directory::Directory(const String& path) :
    _path(path)
    {}

    Result<Array<Directory>> Directory::read(const String& path)
    {
        Array<Directory> directories;

        directories.emplace_back(path);

        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            const auto& entrypath = entry.path().string();

            if (entry.is_regular_file())
            {
                if (entrypath.size() >= 5) // at least length of extension + 1 letter e.g. a.wbl
                {
                    const char *file_extension = &entrypath[entrypath.size() - 4];

                    if (strcmp(file_extension, ".wbl"))
                        continue;

                    auto file = File::read(entrypath);

                    if (!file)
                    {
                        print_error("Not all directory items could be read.");
                        return {};
                    }

                    directories[0].add_file(file.unwrap());
                }
            }
            else if (entry.is_directory())
            {
                auto res = read(entrypath);

                if (!res)
                {
                    print_error("Not all directory items could be read.");
                    return {};
                }

                auto subdirs = res.unwrap();

                directories.reserve(directories.size() + subdirs.size());

                for (auto& dir : subdirs)
                {
                    directories.emplace_back(std::move(dir));
                }
            }
        }

        return directories;
    }

    Directory Directory::from(const char *path, File&& file)
    {
        Directory dir;

        dir._path = path;
        dir._files.emplace_back(std::move(file));

        return dir;
    }
}