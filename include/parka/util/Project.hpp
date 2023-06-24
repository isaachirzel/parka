#ifndef PARKA_UTIL_PROJECT_HPP
#define PARKA_UTIL_PROJECT_HPP

#include "parka/file/Directory.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
    class Project
    {
        String _name;
        Directory _srcDirectory;

        Project(String&& name, Directory&& srcDirectory):
        _name(std::move(name)),
        _srcDirectory(std::move(srcDirectory))
        {}

    public:

        static Project read(const String& path);

        const auto& name() const { return _name; }
        const auto& srcDirectory() const { return _srcDirectory; }
        usize getLinesOfCodeCount();
    };
}

#endif
