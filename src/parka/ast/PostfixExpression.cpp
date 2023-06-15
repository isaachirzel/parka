#include "parka/ast/PostfixExpression.hpp"
#include "parka/enum/TokenType.hpp"
#include "parka/ast/CallExpression.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/SubscriptExpression.hpp"
#include "parka/ast/MemberAccessExpression.hpp"
#include "parka/ast/PrimaryExpression.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	ExpressionSyntax *PostfixExpressionSyntax::parse(Token& token)
	{
		auto postfix = PrimaryExpressionSyntax::parse(token);

		while (true)
		{
			if (!postfix)
				return {};
				
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
