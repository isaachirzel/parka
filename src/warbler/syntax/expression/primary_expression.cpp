#include <warbler/syntax/expression/primary_expression.hpp>

#include <warbler/util/print.hpp>
#include <warbler/syntax/symbol.hpp>
#include <warbler/syntax/expression/constant.hpp>
#include <warbler/syntax/expression/expression.hpp>

namespace warbler::syntax
{
	Result<Ptr<Expression>> PrimaryExpression::parse(lexicon::Token& token)
	{
		if (token.type() == lexicon::TokenType::Identifier)
		{
			auto symbol = Symbol::parse(token.next());

			if (!symbol)
				return {};

			auto *ptr = new Symbol { symbol.unwrap() };

			return Ptr<Expression> (ptr);
		}
		else if (token.type() == lexicon::TokenType::LeftParenthesis)
		{
			token.next();

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
			auto constant = Constant::parse(token.next());

			if (!constant)
				return {};

			auto *ptr = new Constant(constant.unwrap());			

			return Ptr<Expression>(ptr);
		}
	}
}
