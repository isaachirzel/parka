#ifndef PARKA_LOG_LOG_HPP
#define PARKA_LOG_LOG_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/enum/Severity.hpp"
#include "parka/log/Prompt.hpp"
#include "parka/parser/Token.hpp"
#include "parka/util/Print.hpp"
#include <iostream>

namespace parka::log
{
	[[ noreturn ]]
	void fileOpenError(const char* filePath);
	[[ noreturn ]]
	void fileStatError(const char* filePath);
	[[ noreturn ]]
	void fileReadError(const char* filePath);
	[[ noreturn ]]
	void directoryOpenError(const char *directoryPath);
	void invalidTokenError(const Token& token);
	void unterminatedQuoteTokenError(const Token& token);
	void parseError(const Token& token, const char *expected, const char* message = "");
	void parseKeywordError(const Token& token, KeywordType expected, KeywordType found);
	void shadowedParameterError(const Snippet& snippet, const String& name);
	void shadowedLocalEntityError(const Snippet& snippet, const String& symbol, EntityType previousType);
	void shadowedPackageEntityError(const Snippet& snippet, const String& symbol, EntityType previousType);
	void shadowedGlobalEntityError(const Snippet& snippet, const String& symbol, EntityType previousType);
	void undefinedPackageEntityError(const Snippet& snippet, const String& symbol, const String& package);

	template <typename ...Arg>
	[[ noreturn ]]
	void fatal(const char *format, Arg const&...args)
	{
		auto& out = std::cout;
		out << Prompt::from(Severity::Fatal) << ": ";

		_output(out, format, args...);

		out << std::endl;
		
		abort();
	}

	#define notImplemented() parka::log::fatal("$:$: Function $() is not implemented.", __FILE__, __LINE__, __func__)

	usize getDebugCount();
	usize getNoteCount();
	usize getSuccessCount();
	usize getWarningCount();
	usize getErrorCount();
	usize getFatalCount();
}

#endif
