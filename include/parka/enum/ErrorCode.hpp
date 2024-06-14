#ifndef PARKA_ENUM_ERROR_CODE_HPP
#define PARKA_ENUM_ERROR_CODE_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	enum class ErrorCode: u16
	{
		None,
		FileOpenFailed,
		FileStatFailed,
		FileReadFailed,
		DirectoryOpenFailed,
		InvalidToken,
		UnterminatedQuoteToken,
		ParseFailed,
		ParseKeywordFailed,
		ShadowedParameter,
		ShadowedLocalEntity,
		ShadowedPackageEntity,
		ShadowedGlobalEntity,
		UndefinedPackageEntity
	};

	std::ostream& operator<<(std::ostream& out, ErrorCode code);
}

#endif
