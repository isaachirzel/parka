#ifndef PARKA_FS_PROJECT_HPP
#define PARKA_FS_PROJECT_HPP

#include "parka/fs/Directory.hpp"
#include "parka/fs/Path.hpp"

namespace parka::fs
{
    class Project
    {
        String _name;
        Directory _srcDirectory;
        // TODO: Ideas below
        // Directory _configDirectory;
        // Directory _cacheDirectory;

    private:

        Project(String&& name, fs::Directory&& srcDirectory);

    public:

        static Project read(const Path& path);

        const auto& name() const { return _name; }
        const auto& srcDirectory() const { return _srcDirectory; }
        usize getLinesOfCodeCount();
    };
}

#endif
