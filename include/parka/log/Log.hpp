#ifndef PARKA_LOG_LOG_HPP
#define PARKA_LOG_LOG_HPP

#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/EntityType.hpp"
#include "parka/fs/FileSnippet.hpp"
#include "parka/ir/EntityIr.hpp"
#include "parka/ir/TypeIr.hpp"
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
	void fileWriteError(const char* filePath);
	[[ noreturn ]]
	void directoryOpenError(const char* directoryPath);
	void invalidTokenError(const Token& token);
	void unterminatedQuoteTokenError(const Token& token);
	void parseError(const Token& token, const char *expected, const char* message = "");
	void parseKeywordError(const Token& token, KeywordType expected, KeywordType found);
	void invalidCharLiteralError(const fs::FileSnippet& snippet);
	void invalidIntegerLiteralError(const fs::FileSnippet& snippet);
	void typeMismatchError(const fs::FileSnippet& snippet, const ir::TypeIr& givenType, const ir::TypeIr& expectedType);
	void invalidImplicitCastError(const fs::FileSnippet& snippet, const ir::TypeIr& fromType, const ir::TypeIr& toType);
	void invalidExplicitCastError(const fs::FileSnippet& snippet, const ir::TypeIr& fromType, const ir::TypeIr& toType);
	void shadowedParameterError(const fs::FileSnippet& snippet, const String& name);
	void shadowedLocalEntityError(const fs::FileSnippet& snippet, const String& symbol, EntityType previousType);
	void shadowedPackageEntityError(const fs::FileSnippet& snippet, const String& symbol, EntityType previousType);
	void shadowedGlobalEntityError(const fs::FileSnippet& snippet, const String& symbol, EntityType previousType);
	void undefinedEntityError(const ast::QualifiedIdentifierAst& identifier);
	void undefinedPackageEntityError(const fs::FileSnippet& snippet, const String& symbol, const String& package);
	void undefinedBinaryOperatorError(const fs::FileSnippet& snippet, const ir::TypeIr& leftType, BinaryExpressionType binaryExpressionType, const ir::TypeIr& rightType);
	void undefinedAssignmentOperatorError(const fs::FileSnippet& snippet, const ir::TypeIr& leftType, AssignmentType assignmentType, const ir::TypeIr& rightType);
	void entryPointNoParametersAllowedError(const fs::FileSnippet& snippet);
	void entryPointReturnTypeError(const fs::FileSnippet& snippet, const ir::TypeIr& type);
	void invalidReturnValueError(const fs::FileSnippet& snippet, const ir::TypeIr& type, const ir::TypeIr& expectedType);
	void missingReturnValueError(const fs::FileSnippet& snippet, const ir::TypeIr& expectedType);
	void typeAnnotationError(const fs::FileSnippet& snippet, const ir::EntityIr& entity);
	void lValueError(const fs::FileSnippet& snippet);
	void initializationTypeError(const fs::FileSnippet& snippet, const ir::EntityIr& entity, const ir::TypeIr& valueType);
	void invalidBreakError(const fs::FileSnippet& snippet);
	void invalidContinueError(const fs::FileSnippet& snippet);
	void invalidFunctionCallError(const fs::FileSnippet& snippet, const ir::TypeIr& calledType);
	void tooManyArgumentsError(const fs::FileSnippet& snippet);
	void tooFewArgumentsError(const fs::FileSnippet& snippet);
	void incompatibleConditionalTypes(const fs::FileSnippet& snippet);

	template <typename ...Arg>
	void message(Severity severity, const char *format, Arg const&...args)
	{
		auto& out = std::cout;
		out << Prompt::from(severity) << ": ";

		_output(out, format, args...);

		out << "\n\n";
	}

	template <typename ...Arg>
	[[ noreturn ]]
	void fatal(const char *format, Arg const&...args)
	{
		message(Severity::Fatal, format, args...);
		exit(1);
	}

	template <typename ...Arg>
	void debug(const char *format, Arg const&...args)
	{
		message(Severity::Debug, format, args...);
	}

	template <typename ...Arg>
	void success(const char *format, Arg const&...args)
	{
		message(Severity::Success, format, args...);
	}

	#define notImplemented() parka::log::message(Severity::Fatal, "$:$: Function $() is not implemented.", __FILE__, __LINE__, __func__); abort()

	usize getDebugCount();
	usize getNoteCount();
	usize getSuccessCount();
	usize getWarningCount();
	usize getErrorCount();
	usize getFatalCount();
}

#endif
