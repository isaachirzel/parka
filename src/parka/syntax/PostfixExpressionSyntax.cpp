#include "parka/syntax/PostfixExpressionSyntax.hpp"
#include "parka/syntax/CallExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/SubscriptExpressionSyntax.hpp"
#include "parka/syntax/MemberAccessExpressionSyntax.hpp"
#include "parka/syntax/PrimaryExpressionSyntax.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionId> PostfixExpressionSyntax::parse(Token& token)
	{
		auto postfix = PrimaryExpressionSyntax::parse(token);

		if (!postfix)
			return {};

		while (true)
		{
			switch (token.type())
			{
				case TokenType::LeftBracket: // Index
					postfix = SubscriptExpressionSyntax::parse(token, *postfix);
					continue;

				case TokenType::LeftParenthesis: // FunctionSyntax call
					postfix = CallExpressionSyntax::parse(token, *postfix);
					continue;

				case TokenType::Dot: // MemberSyntax
					postfix = MemberAccessExpressionSyntax::parse(token, *postfix);
					continue;
				
				default:
					break;
			}

			break;
		}

		return postfix;
	}
}
