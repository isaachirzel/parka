#include "parka/log/Log.hpp"
#include "parka/enum/ErrorCode.hpp"
#include "parka/file/Snippet.hpp"
#include "parka/log/Prompt.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Print.hpp"
#include <iostream>

namespace parka::log
{
	usize debugCount = 0;
	usize noteCount = 0;
	usize successCount = 0;
	usize warningCount = 0;
	usize errorCount = 0;
	usize fatalCount = 0;

	// TODO: Organize by files
	// TODO: Thread safety
	
	static void addCount(Severity severity)
	{
		switch (severity)
		{
			case Severity::Debug:
				log::debugCount += 1;
				break;

			case Severity::Note:
				log::noteCount += 1;
				break;

			case Severity::Success:
				log::successCount  += 1;
				break;

			case Severity::Warning:
				log::warningCount += 1;
				break;

			case Severity::Error:
				log::errorCount += 1;
				break;

			case Severity::Fatal:
				log::fatalCount += 1;
				break;
		}
	}

	usize getDebugCount() { return debugCount; }
	usize getNoteCount() { return noteCount; }
	usize getSuccessCount() { return successCount; }
	usize getWarningCount() { return warningCount; }
	usize getErrorCount() { return errorCount; }
	usize getFatalCount() { return fatalCount; }

	template <typename ...Arg>
	void logMessage(Severity severity, ErrorCode errorCode, const Position* position, const char* format, Arg const&... args)
	{
		auto& out = std::cout;
		auto prompt = Prompt::from(severity);

		if (position)
			out << position << "\n";

		out << prompt;

		if (errorCode != ErrorCode::None)
			out << " " << errorCode;

		out << ": ";

		_output(out, format, args...);

		out << "\n";

		addCount(severity);
	}

	[[ noreturn ]]
	void fileOpenError(const char* filePath)
	{
		logMessage(
			Severity::Fatal,
			ErrorCode::FileOpenFailed,
			nullptr,
			"Failed to open file `$`.",
			filePath
		);
		abort();
	}

	[[ noreturn ]]
	void fileStatError(const char* filePath)
	{
		logMessage(
			Severity::Fatal,
			ErrorCode::FileStatFailed,
			nullptr,
			"Failed to get information for file `$`.",
			filePath
		);
		abort();
	}

	[[ noreturn ]]
	void fileReadError(const char* filePath)
	{
		logMessage(
			Severity::Fatal,
			ErrorCode::FileReadFailed,
			nullptr,
			"Failed to read data for file `$`.",
			filePath
		);
		abort();
	}

	[[ noreturn ]]
	void directoryOpenError(const char *directoryPath)
	{
		logMessage(
			Severity::Fatal,
			ErrorCode::DirectoryOpenFailed,
			nullptr,
			"Directory `$` does not exist.",
			directoryPath
		);
		abort();
	}

	void invalidTokenError(const Token& token)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidToken,
			&token.snippet().position(),
			"An invalid character was found in the source file."
		);
	}

	void unterminatedQuoteTokenError(const Token& token)
	{
		logMessage(
			Severity::Error,
			ErrorCode::UnterminatedQuoteToken,
			&token.snippet().position(),
			"Token is unterminated."
		);
	}

	void parseError(const Token& token, const char *expected, const char* message)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ParseFailed,
			&token.snippet().position(),
			"Expected $, found `$`. $",
			expected,
			token.type(),
			message
		);
	}

	void parseKeywordError(const Token& token, KeywordType expected, KeywordType found)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ParseKeywordFailed,
			&token.snippet().position(),
			"Expected keyword `$`, found `$`.",
			expected,
			found
		);
	}

	void shadowedParameterError(const Snippet& snippet, const String& name)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ShadowedParameter,
			&snippet.position(),
			"A parameter with the name `$` has already been declared in this parameter list.",
			name
		);
		// TODO: Previously declared here error
	}

	void shadowedLocalEntityError(const Snippet& snippet, const String& symbol, EntityType previousType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ShadowedLocalEntity,
			&snippet.position(),
			"Declaration of variable `$` shadows a $ with the same name.",
			symbol,
			previousType
		);
		// TODO: Previously declared here error
	}

	void shadowedPackageEntityError(const Snippet& snippet, const String& symbol, EntityType previousType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ShadowedPackageEntity,
			&snippet.position(),
			"A $ with the name `$` has already been declared in the package $.",
			previousType,
			symbol
		);
		// TODO: Previously declared here error
	}

	void shadowedGlobalEntityError(const Snippet& snippet, const String& symbol, EntityType previousType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ShadowedLocalEntity,
			&snippet.position(),
			"A $ with the name `$` has already been declared in global scope.",
			previousType,
			symbol
		);
		// TODO: Previously declared here error
	}

	void undefinedPackageEntityError(const Snippet& snippet, const String& symbol, const String& package)
	{
		logMessage(
			Severity::Error,
			ErrorCode::UndefinedPackageEntity,
			&snippet.position(),
			"No definition for `$` could be found in package `$`.",
			symbol,
			package
		);
	}
}
