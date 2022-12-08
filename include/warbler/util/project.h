#ifndef WARBLER_UTIL_PROJECT_H
#define WARBLER_UTIL_PROJECT_H

#include <warbler/util/directory.h>

typedef struct Project
{
    char *name;
    Directory srcDir;
} Project;

Project projectLoad(const char *path);

#endif
