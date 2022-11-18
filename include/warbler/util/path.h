#ifndef WARBLER_UTIL_PATH_H  
#define WARBLER_UTIL_PATH_H  

char *pathJoin(const char *left, const char *right);
char *pathGetRelative(const char *base, const char *path);
void santizePath(char *path);
char *pathDuplicate(const char *path);
const char *pathGetFilenameComponent(const char *path);

#endif
