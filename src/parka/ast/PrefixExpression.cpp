#include "parka/ast/PrefixExpression.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/log/Log.hpp"

namespace parka::ast
{
	static Optional<PrefixType> parsePrefixType(Token& token)
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
				return {};
		}
	}

	ExpressionAst *PrefixExpressionAst::parse(Token& token)
	{
		auto start = Snippet(token);
		auto type = parsePrefixType(token);

		if (!type)
			return ExpressionAst::parsePostfixExpression(token);

		token.increment();

		auto *inner = PrefixExpressionAst::parse(token);

		if (inner == nullptr)
			return nullptr;

		auto snippet = start + inner->snippet();
		auto *syntax = new PrefixExpressionAst(snippet, *type, *inner);

		return syntax;
	}

	ir::ExpressionIr *PrefixExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}