#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/BlockExpressionSyntax.hpp"

namespace parka
{
	FunctionSyntax::FunctionSyntax(PrototypeSyntax&& prototype, ExpressionSyntax& body) :
	_prototype(std::move(prototype)),
	_body(body)
	{}

	static ExpressionSyntax *parseFunctionBody(Token& token)
	{
		if (token.type() == TokenType::DoubleArrow)
		{
			token.increment();

			auto body = ExpressionSyntax::parse(token);

			if (!body)
				return {};

			if (token.type() != TokenType::Semicolon)
			{
				log::parseError(token, "';'", "Inline function bodies need to be ended with ';'.");
				return {};
			}

			token.increment();

			return body;
		}

		if (token.type() == TokenType::LeftBrace)
			return BlockExpressionSyntax::parse(token);
		
		log::parseError(token, "function body", "Functions require a body.");

		return {};
	}

	FunctionSyntax *FunctionSyntax::parse(Token& token)
	{
		auto prototype = PrototypeSyntax::parse(token);

		if (!prototype)
			return {};

		auto body = parseFunctionBody(token);

		if (!body)
			return {};

		auto *syntax = new FunctionSyntax(*prototype, *body);

		return syntax;
	}
}
