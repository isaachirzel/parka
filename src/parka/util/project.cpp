#include "parka/util/project.hpp"

#include "parka/util/path.hpp"


Project projectLoad(const char *path)
{
    char *srcPath = pathJoin(path, "src");

    Project project = {
        .name = pathGetFilename(path),
        .srcDir = directoryRead(srcPath)
    };

    deallocate(srcPath);

    return project;
}
