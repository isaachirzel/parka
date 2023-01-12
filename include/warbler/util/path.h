#ifndef WARBLER_UTIL_PATH_H  
#define WARBLER_UTIL_PATH_H  

#include <warbler/util/primitives.h>

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
char *pathGetCurrentWorkingDirectory(char *buffer);

/**
* @return Directory of application executable
*/
void pathGetExecutableDirectory(char *buffer);

#endif
