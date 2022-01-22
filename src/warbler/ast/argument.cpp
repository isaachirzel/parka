#include <warbler/ast/argument.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>

// standard headers
#include <stdlib.h>
#include <assert.h>

namespace warbler::ast
{
	Argument::Argument(Expression *expr) :
	_expr(expr)
	{}

	Argument::Argument(Argument&& other) :
	_expr(other._expr)
	{
		other._expr = nullptr;
	}

	Argument::Argument(const Argument& other) :
	_expr(new Expression(*other._expr))
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

	Result<Array<Argument>> Argument::parse_list(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_LPAREN)
		{
			error_out(iter) << "expected '(' at start of argument list but got: " << *iter;
			return ERROR_ARGUMENT;
		}

		iter += 1;

		Array<Argument> args;

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
				error_out(iter) << "expected ',' or ')' but got: " << *iter;
				return ERROR_ARGUMENT;
			}
		}

		iter += 1;

		return args;
	}
	
	void Argument::print_tree(u32 depth) const
	{
		_expr->print_tree(depth);
	}

	Argument& Argument::operator=(Argument&& other)
	{
		new(this) auto(other);
		return *this;
	}
	Argument& Argument::operator=(const Argument& other)
	{
		new(this) auto(other);
		return *this;
	}
}
