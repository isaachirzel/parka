#ifndef PARKA_PARSER_PARKA_MODULE_PARSER_HPP
#define PARKA_PARSER_PARKA_MODULE_PARSER_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/ast/Module.hpp"
#include "parka/ast/Operator.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/ast/Variable.hpp"
#include "parka/ast/BinaryExpression.hpp"
#include "parka/ast/CallExpression.hpp"
#include "parka/ast/MemberAccessExpression.hpp"
#include "parka/ast/SubscriptExpression.hpp"
#include "parka/ast/IdentifierExpression.hpp"
#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/PrefixExpression.hpp"
#include "parka/ast/BinaryExpression.hpp"
#include "parka/ast/ConditionalExpression.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/JumpType.hpp"
#include "parka/enum/PrefixType.hpp"
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
		Optional<PrefixType> parsePrefixType();
		Optional<char> parseChar();
		Optional<bool> parseBool();
		Optional<BinaryExpressionType> getMultiplicativeType();
		Optional<BinaryExpressionType> getAdditiveType();
		Optional<BinaryExpressionType> getEqualityType();
		Optional<BinaryExpressionType> parseRelationalType();
		Optional<BinaryExpressionType> parseBitShiftType();
		Optional<BinaryExpressionType> getAssignmentType();
		Optional<JumpType> getJumpType();
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

		Optional<ast::Identifier> parseIdentifier();
		Optional<ast::QualifiedIdentifier> parseQualifiedIdentifier();
		Optional<ast::Operator> parseOperator();
		Optional<ast::PrototypeAst> parsePrototype();
		Optional<ast::TypeAnnotationAst> parseTypeAnnotation();
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
