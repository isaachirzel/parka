#include "parka/ast/Expression.hpp"
#include "parka/ast/AssignmentExpression.hpp"
#include "parka/ast/BoolLiteral.hpp"
#include "parka/ast/CallExpression.hpp"
#include "parka/ast/CharLiteral.hpp"
#include "parka/ast/FloatLiteral.hpp"
#include "parka/ast/IdentifierExpression.hpp"
#include "parka/ast/IntegerLiteral.hpp"
#include "parka/ast/MemberAccessExpression.hpp"
#include "parka/ast/StringLiteral.hpp"
#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/SubscriptExpression.hpp"
#include "parka/log/Log.hpp"

namespace parka::ast
{
	ExpressionAst *ExpressionAst::parse(Token& token)
	{
		if (token.type() == TokenType::LeftBrace)
			return BlockExpressionAst::parse(token);

		return AssignmentExpressionAst::parse(token);
	}

	ExpressionAst *ExpressionAst::parseLiteral(Token& token)
	{
		switch (token.type())
		{
			case TokenType::CharacterLiteral:
				return CharLiteralAst::parse(token);

			case TokenType::StringLiteralAst:
				return StringLiteralAst::parse(token);

			case TokenType::IntegerLiteralAst:
				return IntegerLiteralAst::parse(token);

			case TokenType::FloatLiteralAst:
				return FloatLiteralAst::parse(token);

			case TokenType::Identifier:
				return BoolLiteralAst::parse(token);

			default:
				break;
		}
		
		log::parseError(token, "literal");
		
		return {};
	}

	static ExpressionAst *parseEnclosedExpression(Token& token)
	{
		token.increment();

		auto *expression = ExpressionAst::parse(token);

		if (!expression)
			return {};

		if (token.type() != TokenType::RightParenthesis)
		{
			log::parseError(token, "expected ')' after primary sub-expression");
			return {};
		}

		return expression;
	}

	ExpressionAst *ExpressionAst::parsePrimaryExpression(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Identifier:
				return IdentifierExpressionAst::parse(token);

			case TokenType::LeftParenthesis:
				return parseEnclosedExpression(token);

			default:
				return parseLiteral(token);
		}
	}

	ExpressionAst *ExpressionAst::parsePostfixExpression(Token& token)
	{
		auto postfix = parsePrimaryExpression(token);

		while (true)
		{
			if (!postfix)
				return {};
				
			switch (token.type())
			{
				case TokenType::LeftBracket: // Index
					postfix = SubscriptExpressionAst::parse(token, *postfix);
					continue;

				case TokenType::LeftParenthesis: // FunctionAst call
					postfix = CallExpressionAst::parse(token, *postfix);
					continue;

				case TokenType::Dot: // MemberAst
					postfix = MemberAccessExpressionAst::parse(token, *postfix);
					continue;
				
				default:
					break;
			}

			break;
		}

		return postfix;
	}
}
