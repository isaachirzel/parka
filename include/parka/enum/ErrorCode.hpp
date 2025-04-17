#ifndef PARKA_ENUM_ERROR_CODE_HPP
#define PARKA_ENUM_ERROR_CODE_HPP

#include "parka/util/Common.hpp"

#include <ostream>

namespace parka
{
	enum class ErrorCode: u16
	{
		None,
		FileSystemError,
		InvalidToken,
		ParseError,
		InvalidCharLiteral,
		InvalidIntegerLiteral,
		TypeMismatch,
		InvalidCast,
		InvalidReturnValue,
		ShadowedEntity,
		UndefinedEntity,
		UndefinedOperator,
		InvalidEntryPoint,
		InvalidTypeAnnotation,
		InvalidBreak,
		InvalidContinue,
		InvalidFunctionCall,
		IncorrectArgumentCount,
		IncompatibleConditionalTypes
	};

	std::ostream& operator<<(std::ostream& out, ErrorCode code);
}

#endif
