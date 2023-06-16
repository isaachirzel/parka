#include "parka/ast/CallExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Expression.hpp"

namespace parka
{
	ExpressionSyntax *CallExpressionSyntax::parse(Token& token, ExpressionSyntax& primary)
	{
		auto first = Token(token);
		if (token.type() != TokenType::LeftParenthesis)
		{
			log::parseError(token, "'(' before argument list");
			return {};
		}

		token.increment();

		// TODO: Add initial capacity
		auto arguments = Array<ExpressionSyntax*>();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto *argument = ExpressionSyntax::parse(token);

				if (!argument)
					return {}; // TODO: Continue to next argument by checking for ','

				arguments.push(argument);

				if (token.type() != TokenType::Comma)
					break;

				token.increment();
			}

			if (token.type() != TokenType::RightParenthesis)
			{
				log::parseError(token, "')' after argument list");

				return {};
			}
		}

		auto snippet = first + token;

		token.increment();

		auto *syntax = new CallExpressionSyntax(snippet, primary, std::move(arguments));

		return syntax;
	}

	ExpressionContext *CallExpressionSyntax::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
