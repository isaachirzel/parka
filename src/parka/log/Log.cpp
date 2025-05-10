#include "parka/log/Log.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/enum/ErrorCode.hpp"
#include "parka/enum/Severity.hpp"
#include "parka/fs/FilePosition.hpp"
#include "parka/fs/FileSnippet.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/log/Annotation.hpp"
#include "parka/log/Line.hpp"
#include "parka/log/Prompt.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Print.hpp"
#include <algorithm>
#include <array>
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
				log::successCount += 1;
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
	void logMessage(Severity severity, ErrorCode errorCode, const fs::FilePosition* position, const char* format, Arg const&... args)
	{
		auto& out = std::cout;
		auto prompt = Prompt::from(severity);

		if (position)
			out << *position << "\n";

		out << prompt;

		if (errorCode != ErrorCode::None)
			out << " [" << errorCode << "]";

		out << ": ";

		_output(out, format, args...);

		out << "\n\n";

		addCount(severity);
	}

	template <size_t N, typename = std::enable_if_t<(N > 0), void>>
	void annotate(std::array<Annotation, N> annotations)
	{
		// TODO: Make sure no overlapping annotations, none with same position and none longer than last
		// TODO: Make sure annotations is not empty

		auto snippet = annotations.front().snippet();

		if constexpr (N > 1)
		{
			// These need to be sorted in reverse?

			std::sort(annotations.begin(), annotations.end(), [](const auto& a, const auto& b)
			{
				return b.snippet().position().index() - a.snippet().position().index();
			});

			snippet += annotations.back().snippet();
		}

		std::cout << snippet << '\n';

		// print main snippet, try to figure out highlights in the snippet?
		// print underlines
		// print guide lines
		// print notes
		// shit, annotations need notes
	}

	template <typename ...Args>
	void annotate(Args const&... args)
	{
		annotate(std::array<Annotation, sizeof...(args)> { args... });
	}

	[[ noreturn ]]
	void fileOpenError(const char* filePath)
	{
		logMessage(
			Severity::Fatal,
			ErrorCode::FileSystemError,
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
			ErrorCode::FileSystemError,
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
			ErrorCode::FileSystemError,
			nullptr,
			"Failed to read data for file `$`.",
			filePath
		);
		abort();
	}

	[[ noreturn ]]
	void fileWriteError(const char* filePath)
	{
		logMessage(
			Severity::Fatal,
			ErrorCode::FileSystemError,
			nullptr,
			"Failed to write data to file `$`.",
			filePath
		);
		abort();
	}

	[[ noreturn ]]
	void directoryOpenError(const char *directoryPath)
	{
		logMessage(
			Severity::Fatal,
			ErrorCode::FileSystemError,
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
			ErrorCode::InvalidToken,
			&token.snippet().position(),
			"Token is unterminated."
		);
	}

	void parseError(const Token& token, const char *expected, const char* message)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ParseError,
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
			ErrorCode::ParseError,
			&token.snippet().position(),
			"Expected keyword `$`, found `$`.",
			expected,
			found
		);
	}

	void invalidCharLiteralError(const fs::FileSnippet &snippet)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidCharLiteral,
			&snippet.position(),
			"Char literals must contain exactly 1 characters."
		);
	}

	void invalidIntegerLiteralError(const fs::FileSnippet& snippet)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidIntegerLiteral,
			&snippet.position(),
			"Integer literal is too large to fit in a 64 bit value."
		);
	}

	void typeMismatchError(const fs::FileSnippet& snippet, const ir::TypeIr& givenType, const ir::TypeIr& expectedType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::TypeMismatch,
			&snippet.position(),
			"Expected type `$`, but value was of type `$`.",
			expectedType,
			givenType
		);
	}

	void invalidImplicitCastError(const fs::FileSnippet& snippet, const ir::TypeIr& fromType, const ir::TypeIr& toType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidCast,
			&snippet.position(),
			"Expression with value `$` cannot be implicitly casted to `$`.",
			fromType,
			toType
		);
		// TODO: Add annotation
	}

	void invalidExplicitCastError(const fs::FileSnippet& snippet, const ir::TypeIr& fromType, const ir::TypeIr& toType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidCast,
			&snippet.position(),
			"Expression with value `$` cannot be explicitly casted to `$`.",
			fromType,
			toType
		);
		annotate(
			Annotation(snippet, AnnotationType::Line)
		);
	}

	void shadowedParameterError(const fs::FileSnippet& snippet, const String& name)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ShadowedEntity,
			&snippet.position(),
			"A parameter with the name `$` has already been declared in this parameter list.",
			name
		);
		// TODO: Previously declared here error
	}

	void shadowedLocalEntityError(const fs::FileSnippet& snippet, const String& symbol, EntityType previousType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ShadowedEntity,
			&snippet.position(),
			"Declaration of variable `$` shadows a $ with the same name.",
			symbol,
			previousType
		);
		// TODO: Previously declared here error
	}

	void shadowedPackageEntityError(const fs::FileSnippet& snippet, const String& symbol, EntityType previousType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ShadowedEntity,
			&snippet.position(),
			"A $ with the name `$` has already been declared in the package $.",
			previousType,
			symbol
		);
		// TODO: Previously declared here error
	}

	void shadowedGlobalEntityError(const fs::FileSnippet& snippet, const String& symbol, EntityType previousType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::ShadowedEntity,
			&snippet.position(),
			"A $ with the name `$` has already been declared in global scope.",
			previousType,
			symbol
		);
		// TODO: Previously declared here error
	}

	void undefinedEntityError(const ast::QualifiedIdentifierAst& identifier)
	{
		logMessage(
			Severity::Error,
			ErrorCode::UndefinedEntity,
			&identifier.snippet().position(),
			"No definition for `$` could be found in this scope.",
			identifier
		);
	}

	void undefinedPackageEntityError(const fs::FileSnippet& snippet, const String& symbol, const String& package)
	{
		logMessage(
			Severity::Error,
			ErrorCode::UndefinedEntity,
			&snippet.position(),
			"No definition for `$` could be found in package `$`.",
			symbol,
			package
		);
	}
	
	void undefinedBinaryOperatorError(const fs::FileSnippet& snippet, const ir::TypeIr& leftType, BinaryExpressionType binaryExpressionType, const ir::TypeIr& rightType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::UndefinedOperator,
			&snippet.position(),
			"No binary operator `$ $ $` has been defined.",
			leftType,
			binaryExpressionType,
			rightType
		);
	}

	void undefinedAssignmentOperatorError(const fs::FileSnippet& snippet, const ir::TypeIr& leftType, AssignmentType assignmentType, const ir::TypeIr& rightType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::UndefinedOperator,
			&snippet.position(),
			"No assignment operator `$ $ $` has been defined.",
			leftType,
			assignmentType,
			rightType
		);
	}

	void entryPointNoParametersAllowedError(const fs::FileSnippet& snippet)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidEntryPoint,
			&snippet.position(),
			"Entry point `main` may not have any parameters."
		);
	}

	void entryPointReturnTypeError(const fs::FileSnippet& snippet, const ir::TypeIr& type)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidEntryPoint,
			&snippet.position(),
			"Entry point `main` cannot return $. Return type must be either $ or $.",
			type,
			ir::PrimitiveIr::i32Primitive,
			ir::PrimitiveIr::voidPrimitive
		);
	}


	void invalidReturnValueError(const fs::FileSnippet& snippet, const ir::TypeIr& type, const ir::TypeIr& expectedType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidReturnValue,
			&snippet.position(),
			"Unable to return `$` in function expecting `$`.",
			type,
			expectedType
		);
		// TODO: Highlight function return type
	}

	void missingReturnValueError(const fs::FileSnippet& snippet, const ir::TypeIr& expectedType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidReturnValue,
			&snippet.position(),
			"Expected return value of type `$` but none was given.",
			expectedType
		);
		// TODO: Highlight function return type
	}

	void typeAnnotationError(const fs::FileSnippet& snippet, const ir::EntityIr& entity)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidTypeAnnotation,
			&snippet.position(),
			"Expected a type, but $ `$` was found.",
			entity.entityType,
			entity.symbol()
		);

		// TODO: Figure out what the referred thing was for better clarity
		// TODO: Maybe show "other thing defined here"
	}

	void lValueError(const fs::FileSnippet& snippet)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidTypeAnnotation,
			&snippet.position(),
			"This expression is not a modifiable value."
		);
	}

	void initializationTypeError(const fs::FileSnippet& snippet, const ir::EntityIr& entity, const ir::TypeIr& valueType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::TypeMismatch,
			&snippet.position(),
			"A $ of type `$` cannot be initialized with a value of type `$`.",
			entity.entityType,
			entity.type(),
			valueType
		);
		// TODO: Show entity expected type
	}

	void invalidBreakError(const fs::FileSnippet& snippet)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidBreak,
			&snippet.position(),
			"A break statement cannot be used outside of a loop."
		);
	}

	void invalidContinueError(const fs::FileSnippet& snippet)
	{
		logMessage(
			Severity::Error,
			ErrorCode::InvalidContinue,
			&snippet.position(),
			"A continue statement cannot be used outside of a loop."
		);
	}

	void invalidFunctionCallError(const fs::FileSnippet& snippet, const ir::TypeIr& calledType)
	{
		logMessage(
			Severity::Error,
			ErrorCode::IncorrectArgumentCount,
			&snippet.position(),
			"A `$` cannot be called like a function.",
			calledType
		);
	}

	void tooManyArgumentsError(const fs::FileSnippet& snippet)
	{
		logMessage(
			Severity::Error,
			ErrorCode::IncorrectArgumentCount,
			&snippet.position(),
			"Too many arguments passed into function."
		);
		// TODO: Show how many were expected
		// TODO: Show how many were passed in
		// TODO: Highlight which arguments were too many
	}

	void tooFewArgumentsError(const fs::FileSnippet& snippet)
	{
		logMessage(
			Severity::Error,
			ErrorCode::IncorrectArgumentCount,
			&snippet.position(),
			"Not enough arguments passed into function."
		);
		// TODO: Show how many were expected
		// TODO: Show how many were passed in
		// TODO: Highlight which parameters weren't satisfied
	}

	void incompatibleConditionalTypes(const fs::FileSnippet& snippet)
	{
		logMessage(
			Severity::Error,
			ErrorCode::IncorrectArgumentCount,
			&snippet.position(),
			"Then and else case types are incompatible with each other."
		);
	}
}
