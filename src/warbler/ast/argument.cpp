#include <warbler/ast/argument.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/expression.hpp>

// standard headers
#include <stdlib.h>
#include <assert.h>

namespace warbler
{
	Argument::Argument(Expression *expr) :
	_expr(expr)
	{}

	Argument::~Argument()
	{
		delete _expr;
	}

	Result<Argument> Argument::parse(TokenIterator& iter)
	{
		auto expr = Expression::parse(iter);

		if (expr.has_error())
			return expr.error();

		return Argument(new Expression(expr.unwrap()));
	}

	Result<std::vector<Argument>> Argument::parse_list(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_LPAREN)
		{
			errortf(*iter, "expected '(' at start of argument list but got: %t", &(*iter));
			return ERROR_ARGUMENT;
		}

		iter += 1;

		std::vector<Argument> args;

		if (iter->type() != TOKEN_RPAREN)
		{
			while (true)
			{
				auto res = Argument::parse(iter);

				if (res.has_error())
					return res.error();

				args.emplace_back(res.unwrap());

				if (iter->type() == TOKEN_COMMA)
				{
					iter += 1;
					continue;
				}

				break;
			}
			
			if (iter->type() != TOKEN_RPAREN)
			{
				errortf(*iter, "expected ',' or ')' but got: %t", &(*iter));
			}
		}

		return args;
	}
	
	void Argument::print_tree(u32 depth) const
	{
		_expr->print_tree(depth);
	}
}
