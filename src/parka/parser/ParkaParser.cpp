#include "parka/parser/ParkaParser.hpp"
#include "parka/ast/AssignmentStatementAst.hpp"
#include "parka/ast/BinaryExpressionAst.hpp"
#include "parka/ast/CastExpressionAst.hpp"
#include "parka/ast/CharLiteralAst.hpp"
#include "parka/ast/ConditionalExpressionAst.hpp"
#include "parka/ast/ContinueStatementAst.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/ExpressionStatementAst.hpp"
#include "parka/ast/FloatLiteralAst.hpp"
#include "parka/ast/FunctionBodyAst.hpp"
#include "parka/ast/IfStatementAst.hpp"
#include "parka/ast/IntegerLiteralAst.hpp"
#include "parka/ast/MemberAccessExpressionAst.hpp"
#include "parka/ast/PrefixExpressionAst.hpp"
#include "parka/ast/ReturnStatementAst.hpp"
#include "parka/ast/StringLiteralAst.hpp"
#include "parka/ast/SubscriptExpressionAst.hpp"
#include "parka/ast/YieldStatementAst.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/KeywordType.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Result.hpp"

using namespace parka::ast;

namespace parka::parser
{
	static void logParseError(const Token& token, const char *expected, const char *message = "")
	{
		assert(expected != nullptr);
		assert(message != nullptr);

		log::error(token, "Expected $, found $. $", expected, token.type(), message);
	}

	Ast parse(const Project& project)
	{
		// TODO: Parse external projects
		auto *package = parsePackage(project.srcDirectory(), "");

		assert(package != nullptr);

		auto result = Ast(project.name(), *package);

		return result;
	}

	bool parseSemicolon(Token& token, const char *message)
	{
		if (!token.isSemicolon())
		{
			logParseError(token, "';'", message);
			return false;
		}

		token.increment();

		return true;
	}

	bool parseStatementSemicolon(Token& token)
	{
		return parseSemicolon(token, "Statements must be ended with a ';'.");
	}

	Result<Snippet> parseKeyword(Token& token, KeywordType expected)
	{
		auto type = toKeywordType(token.text());

		if (type != expected)
		{
			log::error(token, "Expected keyword `$`, found $.", expected, token);
			return {};
		}

		auto snippet = Snippet(token);

		token.increment();

		return snippet;
	}

	Result<IdentifierAst> parseIdentifier(Token& token)
	{
		if (!token.isIdentifier())
			return {};

		auto identifier = IdentifierAst(token);

		token.increment();

		return identifier;
	}

	bool parseAbsolute(Token& token)
	{
		if (token.type() != TokenType::Scope)
			return false;

		token.increment();

		return true;
	}

	Result<QualifiedIdentifierAst> parseQualifiedIdentifier(Token& token)
	{
		auto start = Snippet(token);
		auto isAbsolute = parseAbsolute(token);
		auto parts = Array<IdentifierAst>(8);
		
		while (true)
		{
			auto identifier = parseIdentifier(token);

			if (!identifier)
				return {};

			parts.push(*identifier);

			if (token.type() == TokenType::Scope)
			{
				token.increment();
				continue;
			}

			break;
		}

		// Parts is guaranteed to be at least 1 long
		auto snippet = start + parts.back().snippet();
		auto qualifiedIdentifier = QualifiedIdentifierAst(snippet, std::move(parts), isAbsolute);

		return qualifiedIdentifier;
	}

	CharLiteralAst *parseCharLiteral(Token& token)
	{
		if (token.type() != TokenType::CharacterLiteral)
		{
			logParseError(token, "character");
			return {};
		}

		auto *ast = new CharLiteralAst(token);

		token.increment();

		return ast;
	}

	StringLiteralAst *parseStringLiteral(Token& token)
	{
		if (token.type() != TokenType::StringLiteral)
		{
			logParseError(token, "string");
			return {};
		}

		auto *syntax = new StringLiteralAst(token);

		token.increment();

		return syntax;
	}

	Result<bool> parseBool(Token& token)
	{
		auto type = toKeywordType(token.text());

		switch (type)
		{
			case KeywordType::True:
				return true;

			case KeywordType::False:
				return false;

			default:
				break;
		}

		logParseError(token, "`true` or `false`");
		
		return {};
	}

	FloatLiteralAst *parseFloatLiteral(Token& token)
	{
		if (token.type() != TokenType::FloatLiteral)
		{
			logParseError(token, "float");
			return nullptr;
		}

		auto *syntax = new FloatLiteralAst(token);

		token.increment();

		return syntax;
	}

	IntegerLiteralAst *parseIntegerLiteral(Token& token)
	{
		if (token.type() != TokenType::IntegerLiteral)
		{
			logParseError(token, "integer");
			return {};
		}

		auto *syntax = new IntegerLiteralAst(token);

		token.increment();

		return syntax;
	}

	IdentifierExpressionAst *parseIdentifierExpression(Token& token)
	{
		auto identifier = parseQualifiedIdentifier(token);

		if (!identifier)
		{
			logParseError(token, "identifier");
			return {};
		}

		return new IdentifierExpressionAst(*identifier);
	}

	BlockStatementAst *parseBlockStatement(Token& token)
	{
		if (token.type() != TokenType::LeftBrace)
		{
			logParseError(token, "'{' before block");

			return {};
		}

		auto first = Token(token);

		token.increment();

		auto statements = Array<StatementAst*>(16);
		auto encounteredError = false;
		auto seekingNext = false;

		while (token.type() != TokenType::RightBrace)
		{
			if (seekingNext)
			{
				if (!token.isSemicolon())
				{
					token.increment();
					continue;
				}

				token.increment();
				seekingNext = false;
			}

			auto *statement = parseStatement(token);

			if (!statement)
			{
				encounteredError = true;
				seekingNext = true;
				continue;
			}

			statements.push(statement);
		}

		auto last = Token(token);

		token.increment();

		if (encounteredError)
			return {};

		auto *syntax = new BlockStatementAst(first + last, std::move(statements));

		return syntax;
	}

	ExpressionAst *parseExpression(Token& token)
	{
		return parseConditionalExpression(token);
	}

	ExpressionAst *parseEnclosedExpression(Token& token)
	{
		token.increment();

		auto *expression = parseExpression(token);

		if (!expression)
			return {};

		if (token.type() != TokenType::RightParenthesis)
		{
			logParseError(token, "expected ')' after primary sub-expression");
			return {};
		}

		return expression;
	}

	ExpressionAst* parsePrimaryExpression(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Identifier:
			{
				auto text = token.text();
				auto keywordType = toKeywordType(text);

				if (keywordType == KeywordType::True)
				{
					auto *literal = new BoolLiteralAst(token, true);
					
					token.increment();

					return literal;
				}

				if (keywordType == KeywordType::False)
				{
					auto *literal = new BoolLiteralAst(token, false);

					token.increment();

					return literal;
				}
			
				return parseIdentifierExpression(token);
			}

			case TokenType::Scope:
				return parseIdentifierExpression(token);

			case TokenType::LeftParenthesis:
				return parseEnclosedExpression(token);

			case TokenType::CharacterLiteral:
				return parseCharLiteral(token);

			case TokenType::StringLiteral:
				return parseStringLiteral(token);

			case TokenType::IntegerLiteral:
				return parseIntegerLiteral(token);

			case TokenType::FloatLiteral:
				return parseFloatLiteral(token);

			default:
				break;
		}

		logParseError(token, "primary expression");
		return {};
	}

	ExpressionAst *parsePostfixExpression(Token& token)
	{
		auto postfix = parsePrimaryExpression(token);

		while (true)
		{
			if (!postfix)
				return {};
				
			switch (token.type())
			{
				case TokenType::LeftBracket: // Index
					postfix = parseSubscriptExpression(token, *postfix);
					continue;

				case TokenType::LeftParenthesis: // FunctionAst call
					postfix = parseCallExpression(token, *postfix);
					continue;

				case TokenType::Dot: // MemberAst
					postfix = parseMemberAccessExpression(token, *postfix);
					continue;
				
				default:
					break;
			}

			break;
		}

		return postfix;
	}

	CallExpressionAst *parseCallExpression(Token& token, ExpressionAst& primary)
	{
		if (token.type() != TokenType::LeftParenthesis)
		{
			logParseError(token, "'(' before argument list");
			return {};
		}

		token.increment();

		// TODO: Add initial capacity
		auto arguments = Array<ExpressionAst*>();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto *argument = parseExpression(token);

				if (!argument)
					return {}; // TODO: Continue to next argument by checking for ','

				arguments.push(argument);

				if (token.type() != TokenType::Comma)
					break;

				token.increment();
			}

			if (token.type() != TokenType::RightParenthesis)
			{
				logParseError(token, "')' after argument list");

				return {};
			}
		}

		auto snippet = primary.snippet() + token;

		token.increment();

		auto *syntax = new CallExpressionAst(snippet, primary, std::move(arguments));

		return syntax;
	}

	SubscriptExpressionAst *parseSubscriptExpression(Token& token, ExpressionAst& primary)
	{
		if (token.type() != TokenType::LeftBracket)
		{
			logParseError(token, "'['");
			return {};
		}

		token.increment();

		auto index = parseExpression(token);

		if (!index)
			return {};


		if (token.type() != TokenType::RightBracket)
		{
			logParseError(token, "']' after subscript");
			return {};
		}

		auto snippet = primary.snippet() + Snippet(token);
		auto *syntax = new SubscriptExpressionAst(snippet, primary, *index);

		token.increment();

		return syntax;
	}

	MemberAccessExpressionAst *parseMemberAccessExpression(Token& token, ExpressionAst& primary)
	{
		if (token.type() != TokenType::Dot)
		{
			logParseError(token, "'.'");
			return {};
		}

		token.increment();
		
		if (!token.isIdentifier())
		{
			logParseError(token, "member, method, or property name");
			return {};
		}
		
		auto *syntax = new MemberAccessExpressionAst(primary, IdentifierAst(token));

		token.increment();

		return syntax;
	}

	Result<PrefixType> parsePrefixType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Ampersand:
				return PrefixType::Reference;

			case TokenType::Asterisk:
				return PrefixType::Dereference;

			case TokenType::Plus:
				return PrefixType::Positive;

			case TokenType::Minus:
				return PrefixType::Negative;

			case TokenType::BitwiseNot:
				return PrefixType::BitwiseNot;

			case TokenType::BooleanNot:
				return PrefixType::BooleanNot;

			default:
				break;
		}

		return {};
	}

	ExpressionAst *parsePrefixExpression(Token& token)
	{
		auto start = Snippet(token);
		auto type = parsePrefixType(token);

		if (!type)
			return parsePostfixExpression(token);

		token.increment();

		auto *inner = parsePrefixExpression(token);

		if (inner == nullptr)
			return nullptr;

		auto snippet = start + inner->snippet();
		auto *syntax = new PrefixExpressionAst(snippet, *type, *inner);

		return syntax;
	}

	static Result<BinaryExpressionType> parseMultiplicativeType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Modulus:
				return BinaryExpressionType::Modulus;

			case TokenType::Asterisk:
				return BinaryExpressionType::Multiply;

			case TokenType::Slash:
				return BinaryExpressionType::Divide;

			default:
				break;
		}

		return {};
	}

	ExpressionAst* parseCastExpression(Token& token)
	{
		auto* expression = parsePrefixExpression(token);

		if (!expression)
			return {};

		auto keywordType = token.getKeywordType();

		if (keywordType != KeywordType::As)
			return expression;
		
		token.increment();

		auto typeAnnotation = parseTypeAnnotation(token);

		if (!typeAnnotation)
			return {};

		auto snippet = expression->snippet() + typeAnnotation->snippet();

		return new CastExpressionAst(snippet, *expression, *typeAnnotation);
	}

	ExpressionAst *parseMultiplicativeExpression(Token& token)
	{
		auto *lhs = parseCastExpression(token);

		if (!lhs)
			return {};
		
		auto type = parseMultiplicativeType(token);

		while (type)
		{
			token.increment();
			
			auto rhs = parseCastExpression(token);

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = parseMultiplicativeType(token);
		}

		return lhs;
	}

	static Result<BinaryExpressionType> parseAdditiveType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Plus:
				return BinaryExpressionType::Add;

			case TokenType::Minus:
				return BinaryExpressionType::Subtract;

			default:
				break;
		}

		return {};
	}

	ExpressionAst *parseAdditiveExpression(Token& token)
	{
		auto *lhs = parseMultiplicativeExpression(token);

		if (!lhs)
			return {};
		
		auto type = parseAdditiveType(token);

		while (type)
		{
			token.increment();

			auto rhs = parseMultiplicativeExpression(token);

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = parseAdditiveType(token);
		}

		return lhs;
	}

	Result<BinaryExpressionType> parseBitShiftType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::LeftBitShift:
				return BinaryExpressionType::LeftShift;

			case TokenType::RightBitShift:
				return BinaryExpressionType::RightShift;

			default:
				return {};
		}
	}

	ExpressionAst *parseShiftExpression(Token& token)
	{
		auto *lhs = parseAdditiveExpression(token);

		if (!lhs)
			return {};

		auto type = parseBitShiftType(token);

		while (type)
		{
			token.increment();

			auto rhs = parseAdditiveExpression(token);

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = parseBitShiftType(token);
		}

		return lhs;
	}

	Result<BinaryExpressionType> parseRelationalType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::GreaterThan:
				return BinaryExpressionType::GreaterThan;

			case TokenType::LessThan:
				return BinaryExpressionType::LessThan;

			case TokenType::GreaterThanOrEqualTo:
				return BinaryExpressionType::GreaterThanOrEqualTo;

			case TokenType::LessThanOrEqualTo:
				return BinaryExpressionType::LessThanOrEqualTo;

			default:
				return {};
		}
	}
	
	ExpressionAst *parseRelationalExpression(Token& token)
	{
		auto *lhs = parseShiftExpression(token);

		if (!lhs)
			return {};

		auto type = parseRelationalType(token);

		while (type)
		{
			token.increment();

			auto rhs = parseShiftExpression(token);

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = parseRelationalType(token);
		}

		return lhs;
	}

	static Result<BinaryExpressionType> parseEqualityType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Equals:
				return BinaryExpressionType::Equals;

			case TokenType::NotEquals:
				return BinaryExpressionType::NotEquals;

			default:
				return {};
		}
	}

	ExpressionAst *parseEqualityExpression(Token& token)
	{
		auto *lhs = parseRelationalExpression(token);

		if (!lhs)
			return {};

		auto type = parseEqualityType(token);

		while (type)
		{
			token.increment();

			auto rhs = parseRelationalExpression(token);

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = parseEqualityType(token);
		}

		return lhs;
	}

	ExpressionAst *parseBitwiseAndExpression(Token& token)
	{
		auto *lhs = parseEqualityExpression(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Ampersand)
		{
			token.increment();

			auto rhs = parseEqualityExpression(token);

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BitwiseAnd);
		}

		return lhs;
	}

	ExpressionAst *parseBitwiseXorExpression(Token& token)
	{
		auto *lhs = parseBitwiseAndExpression(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto rhs = parseBitwiseAndExpression(token);

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BitwiseXor);
		}

		return lhs;
	}

	ExpressionAst *parseBitwiseOrExpression(Token& token)
	{
		auto *lhs = parseBitwiseXorExpression(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Pipe)
		{
			token.increment();

			auto rhs = parseBitwiseXorExpression(token);

			if (!rhs)
				return {};
			
			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BitwiseOr);
		}

		return lhs;
	}

	ExpressionAst *parseBooleanAndExpression(Token& token)
	{
		auto *lhs = parseBitwiseOrExpression(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanAnd)
		{
			token.increment();

			auto rhs = parseBitwiseOrExpression(token);

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BooleanAnd);
		}

		return lhs;
	}

	ExpressionAst *parseBooleanOrExpression(Token& token)
	{
		auto *lhs = parseBooleanAndExpression(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanOr)
		{
			token.increment();

			auto rhs = parseBooleanAndExpression(token);

			if (!rhs)
				return {};
			
			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BooleanOr);
		}


		return lhs;
	}

	ExpressionAst *parseConditionalExpression(Token& token)
	{
		auto condition = parseBooleanOrExpression(token);

		auto thenKeywordType = token.getKeywordType();

		if (thenKeywordType != KeywordType::Then)
			return condition;

		token.increment();

		auto* trueCase = parseConditionalExpression(token);

		if (!trueCase)
			return {};

		auto elseKeywordType = token.getKeywordType();

		if (elseKeywordType != KeywordType::Else)
		{
			log::error(token, "else case for conditional expression");
			return {};
		}

		token.increment();

		auto falseCase = parseConditionalExpression(token);

		if (!falseCase)
			return {};

		auto *syntax = new ConditionalExpressionAst(*condition, *trueCase, *falseCase);

		return syntax;
	}

	ast::ReturnStatementAst* parseReturnStatement(Token& token)
	{
		auto keyword = parseKeyword(token, KeywordType::Return);

		if (!keyword)
			return {};

		auto* value = (ExpressionAst*)nullptr;

		if (!token.isSemicolon())
		{
			value = parseExpression(token);

			if (!value)
				return {};
		}

		auto snippet = *keyword + token;

		if (!parseStatementSemicolon(token))
			return {};

		return new ReturnStatementAst(snippet, value);
	}

	ast::BreakStatementAst* parseBreakStatement(Token& token)
	{
		auto keyword = parseKeyword(token, KeywordType::Break);

		if (!keyword)
			return {};

		if (!parseStatementSemicolon(token))
			return {};

		return new BreakStatementAst(*keyword);
	}

	ast::ContinueStatementAst* parseContinueStatement(Token& token)
	{
		auto keyword = parseKeyword(token, KeywordType::Continue);

		if (!keyword)
			return {};
		
		if (!parseStatementSemicolon(token))
			return {};

		return new ContinueStatementAst(*keyword);
	}

	ast::YieldStatementAst* parseYieldStatement(Token& token)
	{
		auto keyword = parseKeyword(token, KeywordType::Continue);

		if (!keyword)
			return {};

		auto value = parseExpression(token);

		if (!value)
			return {};

		if (!parseStatementSemicolon(token))
			return {};

		return new YieldStatementAst(*keyword, *value);
	}

	ExpressionStatementAst *parseExpressionStatement(Token& token, bool requireSemicolon)
	{
		auto expression = parseExpression(token);

		if (!expression)
			return {};

		auto snippet = expression->snippet() + Snippet(token);

		if (requireSemicolon && !parseStatementSemicolon(token))
			return {};

		auto *syntax = new ExpressionStatementAst(snippet, *expression);

		return syntax;
	}

	DeclarationStatementAst *parseDeclarationStatement(Token& token, bool requireSemicolon)
	{
		auto *variable = parseVariable(token);

		if (!variable)
			return nullptr;

		if (token.type() != TokenType::Assign)
		{
			logParseError(token, "expected '=' after declaration");
			return nullptr;
		}

		token.increment();

		auto value = parseExpression(token);

		if (!value)
			return nullptr;

		auto snippet = variable->snippet() + Snippet(token);
		
		if (requireSemicolon && !parseStatementSemicolon(token))
			return {};

		auto *syntax = new DeclarationStatementAst(snippet, *variable, *value);

		return syntax;
	}

	ForStatementAst* parseForStatement(Token& token)
	{
		auto forKeyword = parseKeyword(token, KeywordType::For);

		if (!forKeyword)
			return {};

		auto* declaration = parseDeclarationStatement(token);

		if (!declaration)
			return {};

		auto* condition = parseExpression(token);

		if (!condition)
			return {};

		if (!parseSemicolon(token))
			return {};

		auto* action = parseAssignmentStatement(token, false);

		if (!action)
			return {};

		auto* body = parseBlockStatement(token);

		if (!body)
			return {};

		auto snippet = *forKeyword + body->snippet();
		
		return new ForStatementAst(snippet, *declaration, *condition, *action, *body);
	}

	static Result<AssignmentType> parseAssignmentType(Token& token)
	{
		AssignmentType type;

		switch (token.type())
		{
			case TokenType::Assign:
				type = AssignmentType::Assign;
				break;

			case TokenType::MultiplyAssign:
				type = AssignmentType::MultiplyAssign;
				break;

			case TokenType::DivideAssign:
				type = AssignmentType::DivideAssign;
				break;

			case TokenType::ModulusAssign:
				type = AssignmentType::ModulusAssign;
				break;

			case TokenType::AddAssign:
				type = AssignmentType::AddAssign;
				break;

			case TokenType::SubtractAssign:
				type = AssignmentType::SubtractAssign;
				break;

			case TokenType::LeftBitShiftAssign:
				type = AssignmentType::LeftShiftAssign;
				break;

			case TokenType::RightBitShiftAssign:
				type = AssignmentType::RightShiftAssign;
				break;

			case TokenType::BitwiseAndAssign:
				type = AssignmentType::BitwiseAndAssign;
				break;

			case TokenType::BitwiseOrAssign:
				type = AssignmentType::BitwiseOrAssign;
				break;

			case TokenType::BitwiseXorAssign:
				type = AssignmentType::BitwiseXorAssign;
				break;
			
			default:
				logParseError(token, "assignment");
				return {};
		}

		token.increment();

		return type;
	}

	StatementAst* parseAssignmentStatement(Token& token, bool requireSemicolon)
	{
		auto* identifier = parseExpression(token);

		if (!identifier)
			return {};

		if (token.isSemicolon())
		{
			token.increment();
			return new ExpressionStatementAst(identifier->snippet(), *identifier);
		}

		auto type = parseAssignmentType(token);

		if (!type)
			return {};

		auto* value = parseExpression(token);

		if (!value)
			return {};

		auto snippet = identifier->snippet() + (requireSemicolon ? token : value->snippet());

		if (requireSemicolon && !parseStatementSemicolon(token))
			return {};

		return new AssignmentStatementAst(snippet, *identifier, *value, *type);
	}

	IfStatementAst* parseIfStatement(Token& token)
	{
		auto ifKeyword = parseKeyword(token, KeywordType::If);

		if (!ifKeyword)
			return {};

		auto* condition = parseExpression(token);

		if (!condition)
			return {};

		auto* thenCase = parseStatement(token);

		if (!thenCase)
			return {};

		auto elseCase = parseElseCase(token);

		if (!elseCase)
			return {};

		auto endSnippet = *elseCase
			? (*elseCase)->snippet()
			: thenCase->snippet();
		auto snippet = *ifKeyword + endSnippet;

		return new IfStatementAst(snippet, *condition, *thenCase, *elseCase);
	}

	Result<ast::StatementAst*> parseElseCase(Token& token)
	{
		if (!token.isIdentifier())
			return nullptr;

		auto type = toKeywordType(token.text());

		if (type != KeywordType::Else)
			return nullptr;
		
		token.increment();

		auto* elseCase = parseStatement(token);

		if (!elseCase)
			return {};

		return elseCase;
	}

	StatementAst *parseStatement(Token& token)
	{
		if (token.type() == TokenType::LeftBrace)
			return parseBlockStatement(token);

		auto keywordType = toKeywordType(token.text());

		switch (keywordType)
		{

			case KeywordType::Var:
				return parseDeclarationStatement(token);

			case KeywordType::Return:
				return parseReturnStatement(token);

			case KeywordType::Break:
				return parseBreakStatement(token);

			case KeywordType::Continue:
				return parseContinueStatement(token);

			case KeywordType::Yield:
				return parseYieldStatement(token);

			case KeywordType::For:
				return parseForStatement(token);

			case KeywordType::If:
				return parseIfStatement(token);

			default:
				break;
		}

		return parseAssignmentStatement(token);
	}

	bool parseMutability(Token& token)
	{
		if (!token.isIdentifier())
			return false;

		auto keywordType = toKeywordType(token.text());

		if (keywordType != KeywordType::Mut)
			return false;

		return true;
	}

	ParameterAst *parseParameter(Token& token)
	{
		auto first = Snippet(token);
		auto isMutable = parseMutability(token);
		auto identifier = parseIdentifier(token);

		if (!identifier)
		{
			logParseError(token, "parameter name");
			return {};
		}

		if (token.type() != TokenType::Colon)
		{
			logParseError(token, "':'", "Parameters require a type annotation.");
			return {};
		}

		token.increment();

		auto annotation = parseTypeAnnotation(token);

		if (!annotation)
			return {};

		auto snippet = first + annotation->snippet();
		auto *syntax = new ParameterAst(snippet, *identifier, *annotation, isMutable);
		
		return syntax;
	}

	Result<TypeAnnotationAst> parseTypeAnnotation(Token& token)
	{
		auto identifier = parseQualifiedIdentifier(token);

		if (!identifier)
		{
			logParseError(token, "type name");
			return {};
		}

		auto annotation = TypeAnnotationAst(identifier->snippet(), *identifier);

		return annotation;
	}

	VariableAst *parseVariable(Token& token)
	{
		// TODO: VariableAst mutability
		auto keyword = parseKeyword(token, KeywordType::Var);

		if (!keyword)
			return {};	
		
		auto identifier = parseIdentifier(token);

		if (!identifier)
		{
			logParseError(token, "variable name");
			return {};
		}

		auto end = identifier->snippet();

		Optional<TypeAnnotationAst> annotation;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			auto annotationResult = parseTypeAnnotation(token);

			if (!annotationResult)
				return {};

			annotation = *annotationResult;
			end = annotation->snippet();
		}

		auto snippet = *keyword +  end;
		auto *syntax = new VariableAst(snippet, *identifier, false, std::move(annotation));

		return syntax;
	}

	FunctionAst *parseFunction(Token& token)
	{
		auto prototype = parsePrototype(token);

		if (!prototype)
			return {};

		if (token.isSemicolon())
		{
			auto snippet = prototype->snippet() + token;

			token.increment();

			return new FunctionAst(snippet, *prototype, {});
		}

		auto body = parseFunctionBody(token);

		if (!body)
			return {};

		auto snippet = prototype->snippet() + body->snippet();

		return new FunctionAst(snippet, *prototype, *body);
	}


	Result<PrototypeAst> parsePrototype(Token& token)
	{
		auto keyword = parseKeyword(token, KeywordType::Function);

		if (!keyword)
			return {};

		auto identifier = parseIdentifier(token);

		if (!identifier)
		{
			logParseError(token, "function name");
			return {};
		}

		if (token.type() != TokenType::LeftParenthesis)
		{
			logParseError(token, "parameter list");
			return {};
		}

		token.increment();

		auto parameters = Array<ParameterAst*>();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto parameter = parseParameter(token);

				if (!parameter) // TODO: Attempt to fast forward to parameter
					return {};

				parameters.push(parameter);

				if (token.type() == TokenType::Comma)
				{
					token.increment();
					continue;
				}

				break;
			}

			if (token.type() != TokenType::RightParenthesis)
			{
				logParseError(token, "end of parameter list ')'");
				return {};
			}
		}

		auto end = Snippet(token);
		
		token.increment();

		Result<TypeAnnotationAst> returnType;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			returnType = parseTypeAnnotation(token);

			if (!returnType)
				return {};

			end = returnType->snippet();
		}

		auto snippet = *keyword + end;
		auto prototype = PrototypeAst(snippet, *identifier, std::move(parameters), std::move(returnType));

		return prototype;
	}

	Result<FunctionBodyAst> parseFunctionBody(Token& token)
	{
		if (token.type() == TokenType::DoubleArrow)
		{
			auto first = token;

			token.increment();

			auto body = parseExpression(token);

			if (!body)
				return {};

			
			auto snippet = first + token;

			if (!parseSemicolon(token, "Expression function bodies need to be ended with ';'."))
				return {};

			token.increment();

			return FunctionBodyAst(snippet, *body);
		}

		if (token.type() == TokenType::LeftBrace)
		{
			auto body = parseBlockStatement(token);

			if (!body)
				return {};

			return FunctionBodyAst(body->snippet(), *body);
		}
	
		
		logParseError(token, "function body", "Functions require a body.");

		return {};
	}

	bool parsePublicity(Token& token)
	{
		auto keywordType = toKeywordType(token.text());

		if (keywordType == KeywordType::Public)
		{
			token.increment();
			return true;
		}

		if (keywordType == KeywordType::Private)
			token.increment();
		
		return false;
	}

	MemberAst *parseMember(Token& token)
	{
		auto first = Snippet(token);
		bool isPublic = parsePublicity(token);

		auto identifier = parseIdentifier(token);

		if (!identifier)
		{
			logParseError(token, "member name");
			return {};
		}

		if (token.type() != TokenType::Colon)
		{
			logParseError(token, "':''", "TypeIr annotations are required for member declarations.");
			return {};
		}
		
		token.increment();

		auto annotation = parseTypeAnnotation(token);

		if (!annotation)
			return {};
			
		auto snippet = first + annotation->snippet();
		auto *syntax = new MemberAst(snippet, *identifier, *annotation, isPublic);

		return syntax;
	}

	StructAst *parseStruct(Token& token)
	{
		auto keyword = parseKeyword(token, KeywordType::Struct);

		if (!keyword)
			return {};

		auto identifier = parseIdentifier(token);

		if (!identifier)
		{
			logParseError(token, "struct name");
			return {};
		}

		if (token.type() != TokenType::LeftBrace)
		{
			// TODO: 
			logParseError(token, "'{' before member list", "Bodyless structs are not allowed.");
			return {};
		}

		auto members = Array<MemberAst*>();

		token.increment();

		if (token.type() != TokenType::RightBrace)
		{
			while (true)
			{
				auto member = parseMember(token);

				if (!member)
					return {};

				members.push(member);

				if (token.type() == TokenType::Comma)
				{
					token.increment();
					continue;
				}

				break;
			}

			if (token.type() != TokenType::RightBrace)
			{
				logParseError(token, "'}' after struct body");
				return {};
			}
		}

		auto snippet = *keyword + Snippet(token);

		token.increment();

		auto *syntax = new StructAst(snippet, *identifier, std::move(members));

		return syntax;
	}

	ModuleAst parseModule(const File& file)
	{
		auto initial = Token::initial(file);
		auto token = initial;
		auto seekingNext = false;
		auto functions = Array<FunctionAst*>();
		auto structs = Array<StructAst*>();

		while (token.type() != TokenType::EndOfFile)
		{
			auto keywordType = token.isIdentifier()
				? toKeywordType(token.text())
				: KeywordType::None;

			switch (keywordType)
			{
				case KeywordType::Function:
				{
					seekingNext = false;

					auto *function = parseFunction(token);

					if (!function)
						break;

					functions.push(function);

					continue;
				}

				case KeywordType::Struct:
				{
					seekingNext = false;

					auto *strct = parseStruct(token);

					if (!strct)
						break;

					structs.push(strct);

					continue;
				}

				default:
					if (seekingNext)
					{
						token.increment();
						continue;
					}

					logParseError(token, "type or function definition");					
					break;
			}

			seekingNext = true;
		}

		return ModuleAst(String(file.path()), std::move(functions), std::move(structs));
	}

	PackageAst *parsePackage(const Directory& directory, const String& name)
	{
		// TODO: Add multithreading
		auto modules = Array<ModuleAst>(directory.files().length());
		auto packages = Array<PackageAst*>(directory.subdirectories().length());

		for (const auto& file : directory.files())
		{
			auto module = parseModule(file);

			modules.push(std::move(module));
		}

		for (const auto& subdirectory : directory.subdirectories())
			packages.push(parsePackage(subdirectory, subdirectory.name()));

		auto *syntax = new PackageAst(String(name), std::move(modules), std::move(packages));

		return syntax;
	}
}
