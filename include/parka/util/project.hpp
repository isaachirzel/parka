#ifndef PARKA_UTIL_PROJECT_HPP
#define PARKA_UTIL_PROJECT_HPP

#include "parka/util/directory.hpp"

typedef struct Project
{
    char *name;
    Directory srcDir;
} Project;

Project projectLoad(const char *path);

#endif
