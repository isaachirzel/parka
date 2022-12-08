#include <warbler/util/project.h>

#include <warbler/util/path.h>
#include <warbler/util/memory.h>

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
