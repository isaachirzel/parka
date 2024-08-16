#ifndef PARKA_FS_DIRECTORY_HPP
#define PARKA_FS_DIRECTORY_HPP

#include "parka/util/Array.hpp"
#include "parka/fs/File.hpp"

namespace parka::fs
{
    class Directory
    {
        Array<File> _files;
        Array<Directory> _subdirectories;
        Path _path;
        u16 _projectOffset;

    private:

        Directory(Array<File>&& files, Array<Directory>&& subdirectories, Path&& path, u16 projectOffset);

        static Directory readSubdirectory(const Path& path, u16 projectOffset);

    public:

        Directory(Directory&&) = default;
        Directory(const Directory&) = delete;

        static Directory read(const Path& path, u16 projectOffset = 0);
        static Directory createTestSrcDirectory(const Path& projectPath);

        void addFile(File&& file);

        String getRelativePath() const;
        String getName() const;

        const auto& path() const { return _path; }
        const auto& files() const { return _files; }
        const auto& subdirectories() const { return _subdirectories; }
    };
}

#endif
