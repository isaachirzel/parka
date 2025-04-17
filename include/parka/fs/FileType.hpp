#ifndef PARKA_FS_FILE_TYPE_HPP
#define PARKA_FS_FILE_TYPE_HPP

#include "parka/util/Common.hpp"

namespace parka::fs
{
	enum class FileType: u8
	{
		Other,
		ParkaSource,
		Json
	};
}

#endif
