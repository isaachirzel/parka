#include "parka/syntax/CallExpressionSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> CallExpressionSyntax::parse(Token& token, ExpressionSyntaxId primary)
	{
		if (token.type() == TokenType::LeftParenthesis)
		{
			printParseError(token, "'(' before argument list");
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
				printParseError(token, "')' after argument list");

				return {};
			}
		}

		token.increment();

		auto expression = CallExpressionSyntax(std::move(primary), std::move(arguments));
		auto id = SyntaxRepository::add(std::move(expression));

		return id;
	}
}
