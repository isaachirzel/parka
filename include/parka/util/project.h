#ifndef PARKA_UTIL_PROJECT_H
#define PARKA_UTIL_PROJECT_H

#include "parka/util/directory.h"

typedef struct Project
{
    char *name;
    Directory srcDir;
} Project;

Project projectLoad(const char *path);

#endif
