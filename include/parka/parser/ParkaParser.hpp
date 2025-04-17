#ifndef PARKA_PARSER_PARKA_PARSER_HPP
#define PARKA_PARSER_PARKA_PARSER_HPP

#include "parka/ast/Ast.hpp"
#include "parka/ast/BlockStatementAst.hpp"
#include "parka/ast/BoolLiteralAst.hpp"
#include "parka/ast/BreakStatementAst.hpp"
#include "parka/ast/CallExpressionAst.hpp"
#include "parka/ast/CharLiteralAst.hpp"
#include "parka/ast/ContinueStatementAst.hpp"
#include "parka/ast/DeclarationStatementAst.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/ExpressionStatementAst.hpp"
#include "parka/ast/FloatLiteralAst.hpp"
#include "parka/ast/ForStatementAst.hpp"
#include "parka/ast/FunctionBodyAst.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/IdentifierExpressionAst.hpp"
#include "parka/ast/IfStatementAst.hpp"
#include "parka/ast/IntegerLiteralAst.hpp"
#include "parka/ast/MemberAccessExpressionAst.hpp"
#include "parka/ast/PrototypeAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/ast/ReturnStatementAst.hpp"
#include "parka/ast/StatementAst.hpp"
#include "parka/ast/StringLiteralAst.hpp"
#include "parka/ast/SubscriptExpressionAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/ast/VariableAst.hpp"
#include "parka/ast/YieldStatementAst.hpp"
#include "parka/fs/Directory.hpp"
#include "parka/fs/Project.hpp"

namespace parka::parser
{
	ast::Ast parse(const fs::Project& project);
	bool parseSemicolon(Token& token, const char *message = "");
	bool parseStatementSemicolon(Token& token);
	Result<fs::FileSnippet> parseKeyword(Token& token);
	Result<ast::IdentifierAst> parseIdentifier(Token& token);
	Result<ast::QualifiedIdentifierAst> parseQualifiedIdentifier(Token& token);
	Result<ast::TypeAnnotationAst> parseTypeAnnotation(Token& token);
	ast::VariableAst *parseVariable(Token& token);
	bool parseMutability(Token& token);
	ast::FunctionAst *parseFunction(Token& token);
	Result<ast::PrototypeAst> parsePrototype(Token& token);
	ast::ParameterAst *parseParameter(Token& token);
	Result<ast::FunctionBodyAst> parseFunctionBody(Token& token);
	ast::MemberAst *parseMember(Token& token);
	ast::StructAst *parseStruct(Token& token);
	ast::ExpressionAst* parseExpression(Token& token);
	ast::ExpressionAst* parsePrimaryExpression(Token& token);
	ast::ExpressionAst* parsePostfixExpression(Token& token);
	ast::ExpressionAst* parseEnclosedExpression(Token& token);
	ast::ExpressionAst* parseBinaryExpression(Token& token);
	ast::ExpressionAst* parseCastExpression(Token& token);
	ast::CallExpressionAst* parseCallExpression(Token& token, ast::ExpressionAst& primary);
	ast::MemberAccessExpressionAst* parseMemberAccessExpression(Token& token, ast::ExpressionAst& primary);
	ast::SubscriptExpressionAst* parseSubscriptExpression(Token& token, ast::ExpressionAst& primary);
	ast::IdentifierExpressionAst* parseIdentifierExpression(Token& token);
	ast::BlockStatementAst* parseBlockStatement(Token& token);
	ast::ExpressionAst* parsePrefixExpression(Token& token);
	ast::ExpressionAst* parseMultiplicativeExpression(Token& token);
	ast::ExpressionAst* parseAdditiveExpression(Token& token);
	ast::ExpressionAst* parseBitwiseXorExpression(Token& token);
	ast::ExpressionAst* parseBitwiseAndExpression(Token& token);
	ast::ExpressionAst* parseBooleanAndExpression(Token& token);
	ast::ExpressionAst* parseBitwiseOrExpression(Token& token);
	ast::ExpressionAst* parseEqualityExpression(Token& token);
	ast::ExpressionAst* parseRelationalExpression(Token& token);
	ast::ExpressionAst* parseShiftExpression(Token& token);
	ast::ExpressionAst* parseBooleanOrExpression(Token& token);
	ast::ExpressionAst* parseConditionalExpression(Token& token);
	ast::BoolLiteralAst* parseBoolLiteral(Token& token);
	ast::CharLiteralAst* parseCharLiteral(Token& token);
	ast::FloatLiteralAst* parseFloatLiteral(Token& token);
	ast::StringLiteralAst* parseStringLiteral(Token& token);
	ast::IntegerLiteralAst* parseIntegerLiteral(Token& token);
	ast::StatementAst* parseStatement(Token& token);
	ast::DeclarationStatementAst* parseDeclarationStatement(Token& token, bool requireSemicolon = true);
	ast::ExpressionStatementAst* parseExpressionStatement(Token& token, bool requireSemicolon = true);
	ast::ReturnStatementAst* parseReturnStatement(Token& token);
	ast::BreakStatementAst* parseBreakStatement(Token& token);
	ast::ContinueStatementAst* parseContinueStatement(Token& token);
	ast::YieldStatementAst* parseYieldStatement(Token& token);
	ast::ForStatementAst* parseForStatement(Token& token);
	ast::StatementAst* parseAssignmentStatement(Token& token, bool requireSemicolon = true);
	ast::IfStatementAst* parseIfStatement(Token& token);
	Result<ast::StatementAst*> parseElseCase(Token& token);
	ast::ModuleAst parseModule(const fs::File& file);
	ast::PackageAst *parsePackage(const fs::Directory& directory, const String& name);
}

#endif
