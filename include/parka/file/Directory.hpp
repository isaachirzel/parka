#ifndef PARKA_DIRECTORY_HPP
#define PARKA_DIRECTORY_HPP

#include "parka/util/Array.hpp"
#include "parka/file/File.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Path.hpp"

namespace parka
{
    class Directory
    {
        String _name;
        String _path;
        Array<File> _files;
        Array<Directory> _subdirectories;

        Directory(String &&path, Array<File>&& files, Array<Directory>&& subdirectories) :
        _name(path::getFilename(path)),
        _path(std::move(path)),
        _files(std::move(files)),
        _subdirectories(std::move(subdirectories))
        {}

        static Directory readSubdirectory(const String& path, usize offset);

    public:

        Directory(Directory&&) = default;
        Directory(const Directory&) = delete;
        ~Directory() = default;

        static Optional<Directory> read(const String& path, usize pathOffset = 0);

        const auto& name() const { return _name; }
        const auto& path() const { return _path; }
        const auto& files() const { return _files; }
        const auto& subdirectories() const { return _subdirectories; }
    };
}

#endif
