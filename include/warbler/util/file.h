#ifndef WARBLER_UTIL_FILE_H
#define WARBLER_UTIL_FILE_H

#include <warbler/util/string.h>

char *readFileText(const String *filepath);
bool writeFileText(const String *filepath, const String *content);

#endif
