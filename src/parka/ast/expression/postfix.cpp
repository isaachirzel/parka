#include "parka/ast/expression/postfix.hpp"
#include "parka/ast/expression/call.hpp"

#include "parka/ast/expression/expression.hpp"
#include "parka/ast/expression/index.hpp"
#include "parka/ast/expression/member_access.hpp"
#include "parka/ast/expression/primary.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> PostfixExpression::parse(Token& token)
{
	auto postfix = PrimaryExpression::parse(token);

	if (!postfix)
		return {};

	while (true)
	{
		switch (token.type())
		{
			case TokenType::LeftBracket: // Index
				postfix = IndexExpression::parse(token, postfix.unwrap());
				continue;

			case TokenType::LeftParenthesis: // Function call
				postfix = CallExpression::parse(token, postfix.unwrap());
				continue;

			case TokenType::Dot: // Member
				postfix = MemberAccess::parse(token, postfix.unwrap());
				continue;
			
			default:
				break;
		}

		break;
	}

	return postfix;
}
