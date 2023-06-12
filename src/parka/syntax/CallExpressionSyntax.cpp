#include "parka/syntax/CallExpressionSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	CallExpressionSyntax::CallExpressionSyntax(ExpressionSyntax& primary, Array<ExpressionSyntax*>&& arguments) :
	_primary(primary),
	_arguments(std::move(arguments))
	{}

	ExpressionSyntax *CallExpressionSyntax::parse(Token& token, ExpressionSyntax& primary)
	{
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

		token.increment();

		auto *syntax = new CallExpressionSyntax(primary, std::move(arguments));

		return syntax;
	}

	ExpressionContext *CallExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
