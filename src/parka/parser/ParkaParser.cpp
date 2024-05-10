#include "parka/parser/ParkaParser.hpp"
#include "parka/ast/BinaryExpressionAst.hpp"
#include "parka/ast/CharLiteralAst.hpp"
#include "parka/ast/ConditionalExpressionAst.hpp"
#include "parka/ast/ContinueStatementAst.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/ExpressionStatementAst.hpp"
#include "parka/ast/FloatLiteralAst.hpp"
#include "parka/ast/IntegerLiteralAst.hpp"
#include "parka/ast/MemberAccessExpressionAst.hpp"
#include "parka/ast/PrefixExpressionAst.hpp"
#include "parka/ast/ReturnStatementAst.hpp"
#include "parka/ast/StringLiteralAst.hpp"
#include "parka/ast/SubscriptExpressionAst.hpp"
#include "parka/ast/YieldStatementAst.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
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

	bool parseSemicolon(Token& token, const char *message)
	{
		if (token.type() != TokenType::Semicolon)
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

	Result<KeywordAst> parseBoolKeyword(Token& token)
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

	Result<KeywordAst> parseStructKeyword(Token& token)
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

	Result<KeywordAst> parseVarKeyword(Token& token)
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

	Result<KeywordAst> parseFunctionKeyword(Token& token)
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

	Result<KeywordAst> parseOperatorKeyword(Token& token)
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

	Result<KeywordAst> parseMutKeyword(Token& token)
	{
		auto type = toKeywordType(token.text());

		if (type != KeywordType::Mut)
			return {};

		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> parseReturnKeyword(Token& token)
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

	Result<KeywordAst> parseContinueKeyword(Token& token)
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

	Result<KeywordAst> parseBreakKeyword(Token& token)
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

	Result<KeywordAst> parseYieldKeyword(Token& token)
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

	Result<KeywordAst> parseForKeyword(Token& token)
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

	Result<KeywordAst> parseInKeyword(Token& token)
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

	Result<Identifier> parseIdentifier(Token& token)
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

	bool parseAbsolute(Token& token)
	{
		if (token.type() != TokenType::Scope)
			return false;

		token.increment();
		return true;
	}

	Result<QualifiedIdentifier> parseQualifiedIdentifier(Token& token)
	{
		auto start = Snippet(token);
		auto isAbsolute = parseAbsolute(token);
		auto parts = Array<Identifier>(8);
		
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
		auto qualifiedIdentifier = QualifiedIdentifier(snippet, std::move(parts), isAbsolute);

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
			return {};

		return new IdentifierExpressionAst(*identifier);
	}

	BlockExpressionAst *parseBlockExpression(Token& token)
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

		auto *syntax = new BlockExpressionAst(first + last, std::move(statements));

		return syntax;
	}

	ExpressionAst *parseExpression(Token& token)
	{
		if (token.type() == TokenType::LeftBrace)
			return parseBlockExpression(token);

		return parseAssignmentExpression(token);
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

	CallExpressionAst *parseCallExpression(Token& token, ExpressionAst& primary)
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

		auto snippet = first + token;

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
		
		if (token.type() != TokenType::Identifier)
		{
			logParseError(token, "member, method, or property name");
			return {};
		}
		
		auto *syntax = new MemberAccessExpressionAst(primary, Identifier(token));

		token.increment();

		return syntax;
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

	ExpressionAst *parseMultiplicativeExpression(Token& token)
	{
		auto *lhs = parsePrefixExpression(token);

		if (!lhs)
			return {};
		
		auto type = parseMultiplicativeType(token);

		while (type)
		{
			token.increment();
			
			auto rhs = parsePrefixExpression(token);

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
		auto keyword = toKeywordType(token.text());

		if (keyword != KeywordType::Then)
			return condition;

		token.increment();

		auto trueCase = parseConditionalExpression(token);

		if (!trueCase)
			return {};

		keyword = toKeywordType(token.text());

		if (keyword != KeywordType::Else)
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

	Result<BinaryExpressionType> parseAssignmentType(Token& token)
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

	ExpressionAst *parseAssignmentExpression(Token& token)
	{
		auto *lhs = parseConditionalExpression(token);

		if (!lhs)
			return {};

		auto type = parseAssignmentType(token);

		if (!type)
			return lhs;

		token.increment();

		auto rhs = parseConditionalExpression(token);

		if (!rhs)
			return {};

		auto *expression = new BinaryExpressionAst(*lhs, *rhs, *type);

		return expression;
	}

	ast::ReturnStatementAst* parseReturnStatement(Token& token)
	{
		auto keyword = parseReturnKeyword(token);

		if (!keyword)
			return {};

		if (token.type() == TokenType::Semicolon)
		{
			token.increment();

			return new ReturnStatementAst(*keyword);
		}

		auto* value = parseExpression(token);

		if (!value)
			return {};

		if (!parseStatementSemicolon(token))
			return {};

		return new ReturnStatementAst(*keyword, *value);
	}

	ast::BreakStatementAst* parseBreakStatement(Token& token)
	{
		auto keyword = parseBreakKeyword(token);

		if (!keyword)
			return {};

		if (!parseStatementSemicolon(token))
			return {};

		return new BreakStatementAst(*keyword);
	}

	ast::ContinueStatementAst* parseContinueStatement(Token& token)
	{
		auto keyword = parseContinueKeyword(token);

		if (!keyword)
			return {};
		
		if (!parseStatementSemicolon(token))
			return {};

		return new ContinueStatementAst(*keyword);
	}

	ast::YieldStatementAst* parseYieldStatement(Token& token)
	{
		auto keyword = parseYieldKeyword(token);

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
		auto forKeyword = parseForKeyword(token);

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

		auto* action = parseExpressionStatement(token, false);

		if (!action)
			return {};

		auto* body = parseBlockExpression(token);

		if (!body)
			return {};

		auto snippet = forKeyword->snippet() + body->snippet();
		
		return new ForStatementAst(snippet, *declaration, *condition, *action, *body);
	}

	StatementAst *parseStatement(Token& token)
	{
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

			default:
				break;
		}

		return parseExpressionStatement(token);
	}

	ParameterAst *parseParameter(Token& token)
	{
		auto first = Snippet(token);
		auto mutKeyword = parseMutKeyword(token);
		auto isMutable = !!mutKeyword;
		auto identifier = parseIdentifier(token);

		if (!identifier)
			return {};

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

	ExpressionAst *parseFunctionBody(Token& token)
	{
		if (token.type() == TokenType::DoubleArrow)
		{
			token.increment();

			auto body = parseExpression(token);

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
			return parseBlockExpression(token);
		
		logParseError(token, "function body", "Functions require a body.");

		return {};
	}

	Result<TypeAnnotationAst> parseTypeAnnotation(Token& token)
	{
		auto identifier = parseQualifiedIdentifier(token);

		if (!identifier)
			return {};

		auto annotation = TypeAnnotationAst(identifier->snippet(), *identifier);

		return annotation;
	}

	Result<ast::RangeAst> parseRange(Token& token)
	{
		auto start = parseExpression(token);

		if (!start)
			return {};

		if (token.type() != TokenType::Range)
			return RangeAst(*start); 

		token.increment();

		auto end = parseExpression(token);

		if (!end)
			return {};

		return RangeAst(*start, *end);
	}

	VariableAst *parseVariable(Token& token)
	{
		// TODO: VariableAst mutability
		auto keyword = parseVarKeyword(token);

		if (!keyword)
			return {};	
		
		auto identifier = parseIdentifier(token);

		if (!identifier)
			return {};

		auto end = identifier->snippet();

		Result<TypeAnnotationAst> annotation;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			annotation = parseTypeAnnotation(token);

			if (!annotation)
				return {};

			end = annotation->snippet();
		}

		auto snippet = keyword->snippet() +  end;
		auto *syntax = new VariableAst(snippet, *identifier, false, std::move(annotation));

		return syntax;
	}

	Result<PrototypeAst> parsePrototype(Token& token)
	{
		auto keyword = parseFunctionKeyword(token);

		if (!keyword)
			return {};

		auto identifier = parseIdentifier(token);

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

			returnType = parseTypeAnnotation(token);

			if (!returnType)
				return {};

			end = returnType->snippet();
		}

		auto snippet = keyword->snippet() + end;
		auto prototype = PrototypeAst(snippet, *identifier, std::move(parameters), std::move(returnType));

		return prototype;
	}

	FunctionAst *parseFunction(Token& token)
	{
		auto prototype = parsePrototype(token);

		if (!prototype)
			return {};

		auto body = parseFunctionBody(token);

		if (!body)
			return {};

		auto *syntax = new FunctionAst(*prototype, *body);

		return syntax;
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
			return {};

		if (token.type() != TokenType::Colon)
		{
			logParseError(token, "':''", "Type annotations are required for member declarations.");
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
		auto keyword = parseStructKeyword(token);

		if (!keyword)
			return {};

		auto identifier = parseIdentifier(token);

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

		auto snippet = keyword->snippet() + Snippet(token);

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
			auto keywordType = token.type() == TokenType::Identifier
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

				case KeywordType::StructAst:
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

	Ast parse(const Project& project)
	{
		// TODO: Parse external projects
		auto *package = parsePackage(project.srcDirectory(), "");

		assert(package != nullptr);

		auto result = Ast(*package);

		return result;
	}
}
