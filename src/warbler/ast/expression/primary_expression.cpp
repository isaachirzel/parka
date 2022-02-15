#include <warbler/ast/expression/primary_expression.hpp>

#include <warbler/print.hpp>
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/expression/constant.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler::ast
{
	Result<Ptr<Expression>> PrimaryExpression::parse(TokenIterator& iter)
	{
		if (iter->type() == TOKEN_IDENTIFIER)
		{
			auto identifier = Identifier::parse(iter);

			if (!identifier)
				return {};

			return Ptr<Expression> { new Identifier { identifier.unwrap() } };
		}
		else if (iter->type() == TOKEN_LPAREN)
		{
			iter += 1;

			auto expression = Expression::parse(iter);

			if (!expression)
				return {};

			if (iter->type() != TOKEN_RPAREN)
			{
				parse_error(iter, "expected ')' after primary sub-expression");
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

			return Ptr<Expression> { new Constant { constant.unwrap() } };
		}
	}
}
