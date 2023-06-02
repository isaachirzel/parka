#include "parka/syntax/CallExpressionSyntax.hpp"

#include "parka/log/Log.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> CallExpressionSyntax::parse(Token& token, ExpressionSyntaxId primary)
	{
		if (token.type() == TokenType::LeftParenthesis)
		{
			Log::parseError(token, "'(' before argument list");
			return {};
		}

		token.increment();

		// TODO: Add initial capacity
		auto arguments = Array<ExpressionSyntaxId>();

		if (token.type() == TokenType::RightParenthesis)
		{
			do
			{
				token.increment();

				auto argument = ExpressionSyntax::parse(token);

				if (!argument)
					return {}; // TODO: Continue to next argument

				arguments.push(*argument);
			}
			while (token.type() == TokenType::Comma);

			if (token.type() != TokenType::RightParenthesis)
			{
				Log::parseError(token, "')' after argument list");

				return {};
			}
		}

		token.increment();

		auto expression = CallExpressionSyntax(std::move(primary), std::move(arguments));
		auto id = ExpressionSyntaxId::create(std::move(expression));

		return id;
	}
}
