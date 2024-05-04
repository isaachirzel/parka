#ifndef PARKA_PARSER_PARKA_MODULE_PARSER_HPP
#define PARKA_PARSER_PARKA_MODULE_PARSER_HPP

#include "parka/enum/JumpType.hpp"
#include "parka/enum/PrefixType.hpp"
#include "parka/util/Result.hpp"
#include "parka/ast/Module.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/ast/Variable.hpp"
#include "parka/file/File.hpp"
#include "parka/parser/Token.hpp"

namespace parka::parser
{
	class ParkaFileParser
	{
		const File& _file;
		const Token _initialToken;
		Token token;

	private:

		bool parseAbsolute();
		Result<PrefixType> parsePrefixType();
		Result<char> parseChar();
		Result<bool> parseBool();
		Result<BinaryExpressionType> getMultiplicativeType();
		Result<BinaryExpressionType> getAdditiveType();
		Result<BinaryExpressionType> getEqualityType();
		Result<BinaryExpressionType> parseRelationalType();
		Result<BinaryExpressionType> parseBitShiftType();
		Result<BinaryExpressionType> getAssignmentType();
		Result<JumpType> getJumpType();
		bool parsePublicity();

	public:

		ParkaFileParser(const File& file):
		_file(file),
		_initialToken(Token::initial(file)),
		token(_initialToken)
		{}
		ParkaFileParser(ParkaFileParser&&) = default;
		ParkaFileParser(const ParkaFileParser&) = delete;

		ast::ModuleAst parse();

		Result<ast::Identifier> parseIdentifier();
		Result<ast::QualifiedIdentifier> parseQualifiedIdentifier();
		// Result<ast::Operator> parseOperator();
		Result<ast::PrototypeAst> parsePrototype();
		Result<ast::TypeAnnotationAst> parseTypeAnnotation();
		ast::VariableAst *parseVariable();
		ast::ParameterAst *parseParameter();
		ast::ExpressionAst *parseFunctionBody();
		ast::FunctionAst *parseFunction();
		ast::MemberAst *parseMember();
		ast::StructAst *parseStruct();
		
		ast::ExpressionAst *parseExpression();
		ast::ExpressionAst *parsePrimaryExpression();
		ast::ExpressionAst *parsePostfixExpression();
		ast::ExpressionAst *parseEnclosedExpression();
		ast::ExpressionAst *parseBinaryExpression();
		ast::ExpressionAst *parseCallExpression(ast::ExpressionAst& primary);
		ast::ExpressionAst *parseMemberAccessExpression(ast::ExpressionAst& primary);
		ast::ExpressionAst *parseSubscriptExpression(ast::ExpressionAst& primary);
		ast::ExpressionAst *parseIdentifierExpression();
		ast::ExpressionAst *parseBlockExpression();
		ast::ExpressionAst *parsePrefixExpression();
		ast::ExpressionAst *parseMultiplicativeExpression();
		ast::ExpressionAst *parseAdditiveExpression();
		ast::ExpressionAst *parseBitwiseXorExpression();
		ast::ExpressionAst *parseBitwiseAndExpression();
		ast::ExpressionAst *parseAssignmentExpression();
		ast::ExpressionAst *parseBooleanAndExpression();
		ast::ExpressionAst *parseBitwiseOrExpression();
		ast::ExpressionAst *parseEqualityExpression();
		ast::ExpressionAst *parseRelationalExpression();
		ast::ExpressionAst *parseShiftExpression();
		ast::ExpressionAst *parseBooleanOrExpression();
		ast::ExpressionAst *parseConditionalExpression();

		ast::ExpressionAst *parseBoolLiteral();
		ast::ExpressionAst *parseCharLiteral();
		ast::ExpressionAst *parseFloatLiteral();
		ast::ExpressionAst *parseStringLiteral();
		ast::ExpressionAst *parseIntegerLiteral();

		ast::StatementAst *parseStatement();
		ast::StatementAst *parseDeclarationStatement();
		ast::StatementAst *parseExpressionStatement();
		ast::StatementAst *parseJumpStatement();
	};
}

#endif
