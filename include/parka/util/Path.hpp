#ifndef PARKA_UTIL_PATH_H  
#define PARKA_UTIL_PATH_H  

#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"

namespace parka::path
{
	String join(const String& a, const String& b);
	String getFilename(const String& path);
	bool hasExtension(const char *path, const char *extension);
	String getRelativePath(const String& base, const String& path);
	String toAbsolute(const String& path);
	String pathDuplicate(const String& path);
	String getFilename(const String& path);
	usize getParentFolderPathOffset(const String& path);
}

#endif
