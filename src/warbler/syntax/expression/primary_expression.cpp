#include <warbler/syntax/expression/primary_expression.hpp>

#include <warbler/util/print.hpp>
#include <warbler/syntax/expression/symbol.hpp>
#include <warbler/syntax/expression/constant.hpp>
#include <warbler/syntax/expression/expression.hpp>

namespace warbler::syntax
{
	Result<Expression> PrimaryExpression::parse(lexicon::Token& token)
	{
		if (token.type() == lexicon::TokenType::Identifier)
		{
			auto symbol = Symbol::parse(token);

			if (!symbol)
				return {};

			return Expression (Symbol { symbol.unwrap() });
		}
		else if (token.type() == lexicon::TokenType::LeftParenthesis)
		{
			auto expression = Expression::parse(token.next());

			if (!expression)
				return {};

			if (token.type() != lexicon::TokenType::RightParenthesis)
			{
				print_parse_error(token, "expected ')' after primary sub-expression");
				return {};
			}

			token.next();

			return expression.unwrap();
		}
		else
		{
			auto constant = Constant::parse(token);

			if (!constant)
				return {};

			return Expression(Constant(constant.unwrap()));
		}
	}
}
