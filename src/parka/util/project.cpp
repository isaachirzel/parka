#include "parka/util/project.hpp"

#include "parka/util/directory.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/path.hpp"
#include "parka/util/print.hpp"

Optional<Project> Project::read(const String& path)
{
    auto srcPath = path::join(path, "src");
    auto directory = Directory::read(srcPath);

    if (!directory)
        return {};

    print("Reading path: %", path);

    auto name = path::getFilename(path);
    auto project = Project(std::move(name), directory.unwrap());

    return project;
}
