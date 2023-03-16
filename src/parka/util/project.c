#include "parka/util/project.h"

#include "parka/util/path.h"
#include "parka/util/memory.h"

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
