#ifndef PARKA_UTIL_PATH_H  
#define PARKA_UTIL_PATH_H  

#include "parka/util/primitives.h"

void printInit(void);
bool pathHasExtension(const char *path, const char *extension);
char *pathJoin(const char *left, const char *right);
char *pathGetRelative(const char *base, const char *path);
void santizePath(char *path);
char *pathDuplicate(const char *path);
char *pathGetFilename(const char *path);

/**
* @return Current working directory
*/
void pathGetCurrentWorkingDirectory(char *buffer);

/**
* @return Directory of application executable
*/
void pathGetExecutableDirectory(char *buffer);

#endif
