#include "parka/parser/ParkaFileParser.hpp"
#include "parka/ast/BinaryExpressionAst.hpp"
#include "parka/ast/BlockExpressionAst.hpp"
#include "parka/ast/BoolLiteralAst.hpp"
#include "parka/ast/BreakStatementAst.hpp"
#include "parka/ast/CallExpressionAst.hpp"
#include "parka/ast/CharLiteralAst.hpp"
#include "parka/ast/ConditionalExpressionAst.hpp"
#include "parka/ast/ContinueStatementAst.hpp"
#include "parka/ast/DeclarationStatementAst.hpp"
#include "parka/ast/ExpressionStatementAst.hpp"
#include "parka/ast/FloatLiteralAst.hpp"
#include "parka/ast/ForStatementAst.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/IdentifierExpressionAst.hpp"
#include "parka/ast/IntegerLiteralAst.hpp"
#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/MemberAccessExpressionAst.hpp"
#include "parka/ast/PrefixExpressionAst.hpp"
#include "parka/ast/RangeAst.hpp"
#include "parka/ast/ReturnStatementAst.hpp"
#include "parka/ast/StringLiteralAst.hpp"
#include "parka/ast/SubscriptExpressionAst.hpp"
#include "parka/ast/YieldStatementAst.hpp"
#include "parka/enum/KeywordType.hpp"
#include "parka/enum/PrefixType.hpp"
#include "parka/enum/TokenType.hpp"
#include "parka/log/Log.hpp"

using namespace parka::ast;

namespace parka::parser
{
	static void logParseError(const Token& token, const char *expected, const char *message = "")
	{
		assert(expected != nullptr);
		assert(message != nullptr);

		log::error(token, "Expected $, found $. $", expected, token.type(), message);
	}

	ParkaFileParser::ParkaFileParser(const File& file):
		_file(file),
		_initialToken(Token::initial(file)),
		token(_initialToken)
	{}

	bool ParkaFileParser::parseSemicolon(const char *message)
	{
		if (token.type() != TokenType::Semicolon)
		{
			logParseError(token, "';'");
			return false;
		}

		token.increment();

		return true;
	}

	bool ParkaFileParser::parseStatementSemicolon()
	{
		return parseSemicolon("Statements must be ended with a ';'.");
	}

	Result<KeywordAst> ParkaFileParser::parseBoolKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::True && type != KeywordType::False)
		{
			logParseError(token, "`true` or `false`");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();
		
		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseStructKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::StructAst)
		{
			logParseError(token, "`struct` keyword");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseVarKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::Var)
		{
			logParseError(token, "keyword `var");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseFunctionKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::Function)
		{
			logParseError(token, "`function`");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();
		
		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseOperatorKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::Operator)
		{
			logParseError(token, "`operator`");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseMutKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::Mut)
			return {};

		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseReturnKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::Return)
		{
			logParseError(token, "keyword `return`");
			return {};
		}
		
		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseContinueKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::Continue)
		{
			logParseError(token, "keyword `continue`");
		}
		
		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseBreakKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::Break)
		{
			logParseError(token, "keyword `break`");
			return {};
		}
		
		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseYieldKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::Yield)
		{
			logParseError(token, "keyword `yield`");
			return {};
		}
		
		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseForKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::For)
		{
			logParseError(token, "keyword `for`");
			return {};
		}
		
		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> ParkaFileParser::parseInKeyword()
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::In)
		{
			logParseError(token, "keyword `in`");
			return {};
		}
		
		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<Identifier> ParkaFileParser::parseIdentifier()
	{
		if (token.type() != TokenType::Identifier)
		{
			logParseError(token, "identifier");
			return {};
		}

		auto identifier = Identifier(token);

		token.increment();

		return identifier;
	}

	bool ParkaFileParser::parseAbsolute()
	{
		if (token.type() != TokenType::Scope)
			return false;

		token.increment();
		return true;
	}

	Result<QualifiedIdentifier> ParkaFileParser::parseQualifiedIdentifier()
	{
		auto start = Snippet(token);
		auto isAbsolute = parseAbsolute();
		auto parts = Array<Identifier>(8);
		
		while (true)
		{
			auto identifier = parseIdentifier();

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
		auto qualifiedIdentifier = QualifiedIdentifier(snippet, std::move(parts), isAbsolute);

		return qualifiedIdentifier;
	}

	ExpressionAst *ParkaFileParser::parseCharLiteral()
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

	ExpressionAst *ParkaFileParser::parseStringLiteral()
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

	Result<bool> ParkaFileParser::parseBool()
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

	ExpressionAst *ParkaFileParser::parseFloatLiteral()
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

	ExpressionAst *ParkaFileParser::parseIntegerLiteral()
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

	ExpressionAst *ParkaFileParser::parseIdentifierExpression()
	{
		auto identifier = parseQualifiedIdentifier();

		if (!identifier)
			return {};

		return new IdentifierExpressionAst(*identifier);
	}

	ExpressionAst *ParkaFileParser::parseBlockExpression()
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
				if (token.type() != TokenType::Semicolon)
				{
					token.increment();
					continue;
				}

				token.increment();
				seekingNext = false;
			}

			auto *statement = parseStatement();

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

		auto *syntax = new BlockExpressionAst(first + last, std::move(statements));

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseExpression()
	{
		if (token.type() == TokenType::LeftBrace)
			return parseBlockExpression();

		return parseAssignmentExpression();
	}

	ExpressionAst *ParkaFileParser::parseEnclosedExpression()
	{
		token.increment();

		auto *expression = parseExpression();

		if (!expression)
			return {};

		if (token.type() != TokenType::RightParenthesis)
		{
			logParseError(token, "expected ')' after primary sub-expression");
			return {};
		}

		return expression;
	}

	ExpressionAst *ParkaFileParser::parsePrimaryExpression()
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
			
				return parseIdentifierExpression();
			}

			case TokenType::Scope:
				return parseIdentifierExpression();

			case TokenType::LeftParenthesis:
				return parseEnclosedExpression();

			case TokenType::CharacterLiteral:
				return parseCharLiteral();

			case TokenType::StringLiteral:
				return parseStringLiteral();

			case TokenType::IntegerLiteral:
				return parseIntegerLiteral();

			case TokenType::FloatLiteral:
				return parseFloatLiteral();

			default:
				break;
		}

		logParseError(token, "primary expression");
		return {};
	}

	ExpressionAst *ParkaFileParser::parseCallExpression(ExpressionAst& primary)
	{
		auto first = Token(token);
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
				auto *argument = parseExpression();

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

		auto snippet = first + token;

		token.increment();

		auto *syntax = new CallExpressionAst(snippet, primary, std::move(arguments));

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseSubscriptExpression(ExpressionAst& primary)
	{
		if (token.type() != TokenType::LeftBracket)
		{
			logParseError(token, "'['");
			return {};
		}

		token.increment();

		auto index = parseExpression();

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

	ExpressionAst *ParkaFileParser::parseMemberAccessExpression(ExpressionAst& primary)
	{
		if (token.type() != TokenType::Dot)
		{
			logParseError(token, "'.'");
			return {};
		}

		token.increment();
		
		if (token.type() != TokenType::Identifier)
		{
			logParseError(token, "member, method, or property name");
			return {};
		}
		
		auto *syntax = new MemberAccessExpressionAst(primary, Identifier(token));

		token.increment();

		return syntax;
	}

	ExpressionAst *ParkaFileParser::parsePostfixExpression()
	{
		auto postfix = parsePrimaryExpression();

		while (true)
		{
			if (!postfix)
				return {};
				
			switch (token.type())
			{
				case TokenType::LeftBracket: // Index
					postfix = parseSubscriptExpression(*postfix);
					continue;

				case TokenType::LeftParenthesis: // FunctionAst call
					postfix = parseCallExpression(*postfix);
					continue;

				case TokenType::Dot: // MemberAst
					postfix = parseMemberAccessExpression(*postfix);
					continue;
				
				default:
					break;
			}

			break;
		}

		return postfix;
	}

	Result<PrefixType> ParkaFileParser::parsePrefixType()
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

	ExpressionAst *ParkaFileParser::parsePrefixExpression()
	{
		auto start = Snippet(token);
		auto type = parsePrefixType();

		if (!type)
			return parsePostfixExpression();

		token.increment();

		auto *inner = parsePrefixExpression();

		if (inner == nullptr)
			return nullptr;

		auto snippet = start + inner->snippet();
		auto *syntax = new PrefixExpressionAst(snippet, *type, *inner);

		return syntax;
	}

	Result<BinaryExpressionType> ParkaFileParser::getMultiplicativeType()
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

	ExpressionAst *ParkaFileParser::parseMultiplicativeExpression()
	{
		auto *lhs = parsePrefixExpression();

		if (!lhs)
			return {};
		
		auto type = getMultiplicativeType();

		while (type)
		{
			token.increment();
			
			auto rhs = parsePrefixExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = getMultiplicativeType();
		}

		return lhs;
	}

	Result<BinaryExpressionType> ParkaFileParser::getAdditiveType()
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

	ExpressionAst *ParkaFileParser::parseAdditiveExpression()
	{
		auto *lhs = parseMultiplicativeExpression();

		if (!lhs)
			return {};
		
		auto type = getAdditiveType();

		while (type)
		{
			token.increment();

			auto rhs = parseMultiplicativeExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = getAdditiveType();
		}

		return lhs;
	}

	Result<BinaryExpressionType> ParkaFileParser::parseBitShiftType()
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

	ExpressionAst *ParkaFileParser::parseShiftExpression()
	{
		auto *lhs = parseAdditiveExpression();

		if (!lhs)
			return {};

		auto type = parseBitShiftType();

		while (type)
		{
			token.increment();

			auto rhs = parseAdditiveExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = parseBitShiftType();
		}

		return lhs;
	}

	Result<BinaryExpressionType> ParkaFileParser::parseRelationalType()
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
	
	ExpressionAst *ParkaFileParser::parseRelationalExpression()
	{
		auto *lhs = parseShiftExpression();

		if (!lhs)
			return {};

		auto type = parseRelationalType();

		while (type)
		{
			token.increment();

			auto rhs = parseShiftExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = parseRelationalType();
		}

		return lhs;
	}

	Result<BinaryExpressionType> ParkaFileParser::getEqualityType()
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

	ExpressionAst *ParkaFileParser::parseEqualityExpression()
	{
		auto *lhs = parseRelationalExpression();

		if (!lhs)
			return {};

		auto type = getEqualityType();

		while (type)
		{
			token.increment();

			auto rhs = parseRelationalExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, *type);
			type = getEqualityType();
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBitwiseAndExpression()
	{
		auto *lhs = parseEqualityExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::Ampersand)
		{
			token.increment();

			auto rhs = parseEqualityExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BitwiseAnd);
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBitwiseXorExpression()
	{
		auto *lhs = parseBitwiseAndExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto rhs = parseBitwiseAndExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BitwiseXor);
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBitwiseOrExpression()
	{
		auto *lhs = parseBitwiseXorExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::Pipe)
		{
			token.increment();

			auto rhs = parseBitwiseXorExpression();

			if (!rhs)
				return {};
			
			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BitwiseOr);
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBooleanAndExpression()
	{
		auto *lhs = parseBitwiseOrExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanAnd)
		{
			token.increment();

			auto rhs = parseBitwiseOrExpression();

			if (!rhs)
				return {};

			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BooleanAnd);
		}

		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseBooleanOrExpression()
	{
		auto *lhs = parseBooleanAndExpression();

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanOr)
		{
			token.increment();

			auto rhs = parseBooleanAndExpression();

			if (!rhs)
				return {};
			
			lhs = new BinaryExpressionAst(*lhs, *rhs, BinaryExpressionType::BooleanOr);
		}


		return lhs;
	}

	ExpressionAst *ParkaFileParser::parseConditionalExpression()
	{
		auto condition = parseBooleanOrExpression();
		auto keyword = toKeywordType(token.text());

		if (keyword != KeywordType::Then)
			return condition;

		token.increment();

		auto trueCase = parseConditionalExpression();

		if (!trueCase)
			return {};

		keyword = toKeywordType(token.text());

		if (keyword != KeywordType::Else)
		{
			log::error(token, "else case for conditional expression");
			return {};
		}

		token.increment();

		auto falseCase = parseConditionalExpression();

		if (!falseCase)
			return {};

		auto *syntax = new ConditionalExpressionAst(*condition, *trueCase, *falseCase);

		return syntax;
	}

	Result<BinaryExpressionType> ParkaFileParser::getAssignmentType()
	{
		switch (token.type())
		{
			case TokenType::Assign:
				return BinaryExpressionType::Assign;

			case TokenType::MultiplyAssign:
				return BinaryExpressionType::MultiplyAssign;

			case TokenType::DivideAssign:
				return BinaryExpressionType::DivideAssign;

			case TokenType::ModulusAssign:
				return BinaryExpressionType::ModulusAssign;

			case TokenType::AddAssign:
				return BinaryExpressionType::AddAssign;

			case TokenType::SubtractAssign:
				return BinaryExpressionType::SubtractAssign;

			case TokenType::LeftBitShiftAssign:
				return BinaryExpressionType::LeftShiftAssign;

			case TokenType::RightBitShiftAssign:
				return BinaryExpressionType::RightShiftAssign;

			case TokenType::BitwiseAndAssign:
				return BinaryExpressionType::BitwiseAndAssign;

			case TokenType::BitwiseOrAssign:
				return BinaryExpressionType::BitwiseOrAssign;

			case TokenType::BitwiseXorAssign:
				return BinaryExpressionType::BitwiseXorAssign;
			
			default:
				break;
		}

		return {};
	}

	ExpressionAst *ParkaFileParser::parseAssignmentExpression()
	{
		auto *lhs = parseConditionalExpression();

		if (!lhs)
			return {};

		auto type = getAssignmentType();

		if (!type)
			return lhs;

		token.increment();

		auto rhs = parseConditionalExpression();

		if (!rhs)
			return {};

		auto *expression = new BinaryExpressionAst(*lhs, *rhs, *type);

		return expression;
	}

	ast::StatementAst* ParkaFileParser::parseReturnStatement()
	{
		auto keyword = parseReturnKeyword();

		if (!keyword)
			return {};

		if (token.type() == TokenType::Semicolon)
		{
			token.increment();

			return new ReturnStatementAst(*keyword);
		}

		auto* value = parseExpression();

		if (!value)
			return {};

		if (!parseStatementSemicolon())
			return {};

		return new ReturnStatementAst(*keyword, *value);
	}

	ast::StatementAst* ParkaFileParser::parseBreakStatement()
	{
		auto keyword = parseBreakKeyword();

		if (!keyword)
			return {};

		if (!parseStatementSemicolon())
			return {};

		return new BreakStatementAst(*keyword);
	}

	ast::StatementAst* ParkaFileParser::parseContinueStatement()
	{
		auto keyword = parseContinueKeyword();

		if (!keyword)
			return {};
		
		if (!parseStatementSemicolon())
			return {};

		return new ContinueStatementAst(*keyword);
	}

	ast::StatementAst* ParkaFileParser::parseYieldStatement()
	{
		auto keyword = parseYieldKeyword();

		if (!keyword)
			return {};

		auto value = parseExpression();

		if (!value)
			return {};

		if (!parseStatementSemicolon())
			return {};

		return new YieldStatementAst(*keyword, *value);
	}

	StatementAst *ParkaFileParser::parseExpressionStatement()
	{
		auto expression = parseExpression();

		if (!expression)
			return {};

		auto snippet = expression->snippet() + Snippet(token);

		if (!parseStatementSemicolon())
			return {};

		auto *syntax = new ExpressionStatementAst(snippet, *expression);

		return syntax;
	}

	DeclarationStatementAst *ParkaFileParser::parseDeclarationStatement()
	{
		auto *variable = parseVariable();

		if (!variable)
			return nullptr;

		if (token.type() != TokenType::Assign)
		{
			logParseError(token, "expected '=' after declaration");
			return nullptr;
		}

		token.increment();

		auto value = parseExpression();

		if (!value)
			return nullptr;

		auto snippet = variable->snippet() + Snippet(token);
		
		if (!parseStatementSemicolon())
			return {};

		auto *syntax = new DeclarationStatementAst(snippet, *variable, *value);

		return syntax;
	}

	StatementAst* ParkaFileParser::parseForStatement()
	{
		auto forKeyword = parseForKeyword();

		if (!forKeyword)
			return {};

		auto* declaration = parseDeclarationStatement();

		if (!declaration)
			return {};

		auto* condition = parseExpression();

		if (!condition)
			return {};

		if (!parseSemicolon())
			return {};

		auto* action = parseExpression();

		if (!action)
			return {};

		auto* body = parseBlockExpression();

		if (!body)
			return {};

		auto snippet = forKeyword->snippet() + body->snippet();
		
		return new ForStatementAst(snippet, *declaration, *condition, *action, *body);
	}

	StatementAst *ParkaFileParser::parseStatement()
	{
		auto keywordType = toKeywordType(token.text());

		switch (keywordType)
		{
			case KeywordType::Var:
				return parseDeclarationStatement();

			case KeywordType::Return:
				return parseReturnStatement();

			case KeywordType::Break:
				return parseBreakStatement();

			case KeywordType::Continue:
				return parseContinueStatement();

			case KeywordType::Yield:
				return parseYieldStatement();

			case KeywordType::For:
				return parseForStatement();

			default:
				break;
		}

		return parseExpressionStatement();
	}

	ParameterAst *ParkaFileParser::parseParameter()
	{
		auto first = Snippet(token);
		auto mutKeyword = parseMutKeyword();
		auto isMutable = !!mutKeyword;
		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			logParseError(token, "':'", "Parameters require a type annotation.");
			return {};
		}

		token.increment();

		auto annotation = parseTypeAnnotation();

		if (!annotation)
			return {};

		auto snippet = first + annotation->snippet();
		auto *syntax = new ParameterAst(snippet, *identifier, *annotation, isMutable);
		
		return syntax;
	}

	ExpressionAst *ParkaFileParser::parseFunctionBody()
	{
		if (token.type() == TokenType::DoubleArrow)
		{
			token.increment();

			auto body = parseExpression();

			if (!body)
				return {};

			if (token.type() != TokenType::Semicolon)
			{
				log::error(token, "Inline function bodies need to be ended with ';'.");
				return {};
			}

			token.increment();

			return body;
		}

		if (token.type() == TokenType::LeftBrace)
			return parseBlockExpression();
		
		logParseError(token, "function body", "Functions require a body.");

		return {};
	}

	Result<TypeAnnotationAst> ParkaFileParser::parseTypeAnnotation()
	{
		auto identifier = parseQualifiedIdentifier();

		if (!identifier)
			return {};

		auto annotation = TypeAnnotationAst(identifier->snippet(), *identifier);

		return annotation;
	}

	Result<ast::RangeAst> ParkaFileParser::parseRange()
	{
		auto start = parseExpression();

		if (!start)
			return {};

		if (token.type() != TokenType::Range)
			return RangeAst(*start); 

		token.increment();

		auto end = parseExpression();

		if (!end)
			return {};

		return RangeAst(*start, *end);
	}

	VariableAst *ParkaFileParser::parseVariable()
	{
		// TODO: VariableAst mutability
		auto keyword = parseVarKeyword();

		if (!keyword)
			return {};	
		
		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

		auto end = identifier->snippet();

		Result<TypeAnnotationAst> annotation;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			annotation = parseTypeAnnotation();

			if (!annotation)
				return {};

			end = annotation->snippet();
		}

		auto snippet = keyword->snippet() +  end;
		auto *syntax = new VariableAst(snippet, *identifier, false, std::move(annotation));

		return syntax;
	}

	Result<PrototypeAst> ParkaFileParser::parsePrototype()
	{
		auto keyword = parseFunctionKeyword();

		if (!keyword)
			return {};

		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

		if (token.type() != TokenType::LeftParenthesis)
		{
			logParseError(token, "'(' after function name");
			return {};
		}

		token.increment();

		auto parameters = Array<ParameterAst*>();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto parameter = parseParameter();

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
				logParseError(token, "')'", "Invalid tokens in parameter list");
				return {};
			}
		}

		auto end = Snippet(token);
		
		token.increment();

		Result<TypeAnnotationAst> returnType;

		if (token.type() == TokenType::SingleArrow)
		{
			token.increment();

			returnType = parseTypeAnnotation();

			if (!returnType)
				return {};

			end = returnType->snippet();
		}

		auto snippet = keyword->snippet() + end;
		auto prototype = PrototypeAst(snippet, *identifier, std::move(parameters), std::move(returnType));

		return prototype;
	}

	FunctionAst *ParkaFileParser::parseFunction()
	{
		auto prototype = parsePrototype();

		if (!prototype)
			return {};

		auto body = parseFunctionBody();

		if (!body)
			return {};

		auto *syntax = new FunctionAst(*prototype, *body);

		return syntax;
	}

	bool ParkaFileParser::parsePublicity()
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

	MemberAst *ParkaFileParser::parseMember()
	{
		auto first = Snippet(token);
		bool isPublic = parsePublicity();

		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			logParseError(token, "':''", "Type annotations are required for member declarations.");
			return {};
		}
		
		token.increment();

		auto annotation = parseTypeAnnotation();

		if (!annotation)
			return {};
			
		auto snippet = first + annotation->snippet();
		auto *syntax = new MemberAst(snippet, *identifier, *annotation, isPublic);

		return syntax;
	}

	StructAst *ParkaFileParser::parseStruct()
	{
		auto keyword = parseStructKeyword();

		if (!keyword)
			return {};

		auto identifier = parseIdentifier();

		if (!identifier)
			return {};

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
				auto member = parseMember();

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

		auto snippet = keyword->snippet() + Snippet(token);

		token.increment();

		auto *syntax = new StructAst(snippet, *identifier, std::move(members));

		return syntax;
	}

	ModuleAst ParkaFileParser::parse()
	{
		auto seekingNext = false;
		auto functions = Array<FunctionAst*>();
		auto structs = Array<StructAst*>();

		while (token.type() != TokenType::EndOfFile)
		{
			auto keywordType = token.type() == TokenType::Identifier
				? toKeywordType(token.text())
				: KeywordType::None;

			switch (keywordType)
			{
				case KeywordType::Function:
				{
					seekingNext = false;

					auto *function = parseFunction();

					if (!function)
						break;

					functions.push(function);

					continue;
				}

				case KeywordType::StructAst:
				{
					seekingNext = false;

					auto *strct = parseStruct();

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

		return ModuleAst(String(_file.path()), std::move(functions), std::move(structs));
	}
}
