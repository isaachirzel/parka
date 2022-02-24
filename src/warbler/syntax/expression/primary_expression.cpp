#include <warbler/syntax//expression/primary_expression.hpp>

#include <warbler/util/print.hpp>
#include <warbler/syntax//symbol.hpp>
#include <warbler/syntax//expression/constant.hpp>
#include <warbler/syntax//expression/expression.hpp>

namespace warbler::syntax
{
	Result<Ptr<Expression>> PrimaryExpression::parse(lexicon::TokenIterator& iter)
	{
		if (iter->type() == lexicon::TOKEN_IDENTIFIER)
		{
			auto symbol = Symbol::parse(iter);

			if (!symbol)
				return {};

			auto *ptr = new Symbol { symbol.unwrap() };

			return Ptr<Expression> (ptr);
		}
		else if (iter->type() == lexicon::TOKEN_LPAREN)
		{
			iter += 1;

			auto expression = Expression::parse(iter);

			if (!expression)
				return {};

			if (iter->type() != lexicon::TOKEN_RPAREN)
			{
				print_parse_error(iter, "expected ')' after primary sub-expression");
				return {};
			}

			iter += 1;

			return expression.unwrap();
		}
		else
		{
			auto constant = Constant::parse(iter);

			if (!constant)
				return {};

			auto *ptr = new Constant(constant.unwrap());			

			return Ptr<Expression>(ptr);
		}
	}
}
