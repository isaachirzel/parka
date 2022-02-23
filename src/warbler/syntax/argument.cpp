#include <warbler/syntax//argument.hpp>

// local headers
#include <warbler/util/print.hpp>
#include <warbler/syntax//expression/expression.hpp>

// standard headers
#include <stdlib.h>
#include <assert.h>

namespace warbler::syntax
{
	Argument::Argument(Ptr<Expression>&& expr) :
	_expr(std::move(expr))
	{}

	Result<Argument> Argument::parse(TokenIterator& iter)
	{
		auto expr = Expression::parse(iter);

		if (!expr)
			return {};

		return Argument { expr.unwrap() };
	}

	Result<Array<Argument>> Argument::parse_list(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_LPAREN)
		{
			error_out(iter) << "expected '(' at start of argument list but got: " << *iter;
			return {};
		}

		iter += 1;

		Array<Argument> args;

		if (iter->type() != TOKEN_RPAREN)
		{
			while (true)
			{
				auto res = Argument::parse(iter);

				if (!res)
					return {};

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
				return {};
			}
		}

		iter += 1;

		return args;
	}
	
	bool Argument::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		return _expr->validate(mod_ctx, func_ctx);
	}

	void Argument::print_tree(u32 depth) const
	{
		_expr->print_tree(depth);
	}
}
