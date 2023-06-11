#ifndef PARKA_PARSER_PARKA_PARSER_HPP
#define PARKA_PARSER_PARKA_PARSER_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/MemberSyntax.hpp"
#include "parka/syntax/PrototypeSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/syntax/VariableSyntax.hpp"

namespace parka
{
	class ParkaParser
	{
		Token token;

	public:

		ParkaParser(const Project& project) :
		_	

		SyntaxTree parseSyntaxTree(const Project& project);
		PackageSyntax parsePackage(const Directory& directory, const String& name);
		ModuleSyntax parseModule(const File& file);
		Optional<StructSyntax> parseStruct(Token& token);
		Optional<MemberSyntax> parseMember(Token& token);
		Optional<TypeAnnotationSyntax> parseTypeAnnotation(Token& token);
		Optional<QualifiedIdentifier> parseQualifiedIdentifier(Token& token);
		Optional<Identifier> parseIdentifier(Token& token);
		Optional<FunctionSyntax> parseFunction(Token& token);
		Optional<PrototypeSyntax> parsePrototype(Token& token);
		Optional<ParameterSyntax> parseParameter(Token& token);
		Optional<KeywordSyntax> parseKeyword(Token& token);
		Optional<VariableSyntax> parseVariable(Token& token);
		ExpressionSyntax *parseExpression(Token& token);
		ExpressionSyntax *parseAdditiveExpression(Token& token);
		ExpressionSyntax *parseAssignmentExpression(Token& token);
		ExpressionSyntax *parseBitwiseAndExpression(Token& token);
		ExpressionSyntax *parseBitwiseOrExpression(Token& token);
		ExpressionSyntax *parseBitwiseXorExpression(Token& token);
		ExpressionSyntax *parseBlockExpression(Token& token);
		ExpressionSyntax *parseBooleanAndExpression(Token& token);
		ExpressionSyntax *parseBooleanOrExpression(Token& token);
		ExpressionSyntax *parseCallExpression(Token& token);
		ExpressionSyntax *parseConditionalExpression(Token& token);
		ExpressionSyntax *parseEqualityExpression(Token& token);
		ExpressionSyntax *parseIdentifierExpression(Token& token);
		ExpressionSyntax *parseIfExpression(Token& token);
		ExpressionSyntax *parseSubscriptExpression(Token& token);
		ExpressionSyntax *parseMemberAccessExpression(Token& token);
		ExpressionSyntax *parseMultiplicativeExpression(Token& token);
		ExpressionSyntax *parsePrefixExpression(Token& token);
		ExpressionSyntax *parseRelationalExpression(Token& token);
		ExpressionSyntax *parseShiftExpression(Token& token);
		ExpressionSyntax *parseBoolLiteral(Token& token);
		ExpressionSyntax *parseCharLiteral(Token& token);
		ExpressionSyntax *parseFloatLiteral(Token& token);
		ExpressionSyntax *parseIntegerLiteral(Token& token);
		ExpressionSyntax *parseStringLiteral(Token& token);
		StatementSyntax *parseStatement(Token& token);
		StatementSyntax *parseDeclarationStatement(Token& token);
		StatementSyntax *parseExpressionStatement(Token& token);
		StatementSyntax *parseJumpStatement(Token& token);
	}
}

#endif
