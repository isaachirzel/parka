#include "parka/ast/postfix_expression.hpp"
#include "parka/ast/call_expression.hpp"
#include "parka/ast/expression.hpp"
#include "parka/ast/subscript_expression.hpp"
#include "parka/ast/member_access_expression.hpp"
#include "parka/ast/primary_expression.hpp"
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
				postfix = IndexExpression::parse(token, *postfix);
				continue;

			case TokenType::LeftParenthesis: // Function call
				postfix = CallExpression::parse(token, *postfix);
				continue;

			case TokenType::Dot: // Member
				postfix = MemberAccess::parse(token, *postfix);
				continue;
			
			default:
				break;
		}

		break;
	}

	return postfix;
}
