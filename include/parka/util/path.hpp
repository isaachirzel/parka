#ifndef PARKA_UTIL_PATH_H  
#define PARKA_UTIL_PATH_H  

#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

namespace path
{
	String join(const String& a, const String& b);
	String getFilename(const String& path);
	bool hasExtension(const char *path, const char *extension);
	String getRelativePath(const String& base, const String& path);
	void santizePath(String& path);
	String pathDuplicate(const String& path);
	String getFilename(const String& path);
}

#endif
