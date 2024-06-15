#ifndef PARKA_LOG_LOG_HPP
#define PARKA_LOG_LOG_HPP

#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/EntityType.hpp"
#include "parka/file/Snippet.hpp"
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
	void directoryOpenError(const char* directoryPath);
	void invalidTokenError(const Token& token);
	void unterminatedQuoteTokenError(const Token& token);
	void parseError(const Token& token, const char *expected, const char* message = "");
	void parseKeywordError(const Token& token, KeywordType expected, KeywordType found);
	void invalidCharLiteralError(const Snippet& snippet);
	void invalidIntegerLiteralError(const Snippet& snippet);
	void typeMismatchError(const Snippet& snippet, const ir::TypeIr& givenType, const ir::TypeIr& expectedType);
	void invalidImplicitCastError(const Snippet& snippet, const ir::TypeIr& fromType, const ir::TypeIr& toType);
	void invalidExplicitCastError(const Snippet& snippet, const ir::TypeIr& fromType, const ir::TypeIr& toType);
	void shadowedParameterError(const Snippet& snippet, const String& name);
	void shadowedLocalEntityError(const Snippet& snippet, const String& symbol, EntityType previousType);
	void shadowedPackageEntityError(const Snippet& snippet, const String& symbol, EntityType previousType);
	void shadowedGlobalEntityError(const Snippet& snippet, const String& symbol, EntityType previousType);
	void undefinedEntityError(const ast::QualifiedIdentifierAst& identifier);
	void undefinedPackageEntityError(const Snippet& snippet, const String& symbol, const String& package);
	void undefinedBinaryOperatorError(const Snippet& snippet, const ir::TypeIr& leftType, BinaryExpressionType binaryExpressionType, const ir::TypeIr& rightType);
	void undefinedAssignmentOperatorError(const Snippet& snippet, const ir::TypeIr& leftType, AssignmentType assignmentType, const ir::TypeIr& rightType);
	void entryPointNoParametersAllowedError(const Snippet& snippet);
	void entryPointReturnTypeError(const Snippet& snippet, const ir::TypeIr& type);
	void invalidReturnValueError(const Snippet& snippet, const ir::TypeIr& type, const ir::TypeIr& expectedType);
	void missingReturnValueError(const Snippet& snippet, const ir::TypeIr& expectedType);
	void typeAnnotationError(const Snippet& snippet, const ir::EntityIr& entity);
	void lValueError(const Snippet& snippet);
	void initializationTypeError(const Snippet& snippet, const ir::EntityIr& entity, const ir::TypeIr& valueType);
	void invalidBreakError(const Snippet& snippet);
	void invalidContinueError(const Snippet& snippet);
	void invalidFunctionCallError(const Snippet& snippet, const ir::TypeIr& calledType);
	void tooManyArgumentsError(const Snippet& snippet);
	void tooFewArgumentsError(const Snippet& snippet);
	void incompatibleConditionalTypes(const Snippet& snippet);

	template <typename ...Arg>
	void message(Severity severity, const char *format, Arg const&...args)
	{
		auto& out = std::cout;
		out << Prompt::from(severity) << ": ";

		_output(out, format, args...);

		out << std::endl;
	}

	template <typename ...Arg>
	[[ noreturn ]]
	void fatal(const char *format, Arg const&...args)
	{
		message(Severity::Fatal, format, args...);
		#ifndef NDEBUG
		abort();
		#else
		exit(1);
		#endif
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

	#define notImplemented() parka::log::fatal("$:$: Function $() is not implemented.", __FILE__, __LINE__, __func__)

	usize getDebugCount();
	usize getNoteCount();
	usize getSuccessCount();
	usize getWarningCount();
	usize getErrorCount();
	usize getFatalCount();
}

#endif
