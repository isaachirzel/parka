#ifndef PARKA_UTIL_PROJECT_HPP
#define PARKA_UTIL_PROJECT_HPP

#include "parka/util/directory.hpp"
#include "parka/util/optional.hpp"

class Project
{
    String _name;
    Directory _srcDirectory;

    Project(String&& name, Directory&& srcDirectory) :
    _name(std::move(name)),
    _srcDirectory(std::move(srcDirectory))
    {}

public:

    static Optional<Project> read(const String& path);

    const auto& name() const { return _name; }
    const auto& srcDirectory() const { return _srcDirectory; }
};

#endif
