#ifndef WARBLER_FILE_TREE_HPP
#define WARBLER_FILE_TREE_HPP

#include <warbler/file.hpp>

namespace warbler
{
    class Directory
    {
    private:

        String _path;
        Array<File> _files;

    public:

        Directory() = default;
        Directory(const String& path);

        static Result<Array<Directory>> read(const String& path);

        void add_file(File&& file)
        {
            _files.emplace_back(std::move(file));
        }

        const auto& path() const { return _path; }
        const auto& files() const { return _files; }
        bool is_empty() const { return _files.empty(); }
    };
}

#endif
