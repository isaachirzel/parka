#include <warbler/ast/expression/additive_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	AdditiveExpression::AdditiveExpression(MultiplicativeExpression&& lhs, Array<AdditiveRhs>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<AdditiveExpression> AdditiveExpression::parse(TokenIterator& iter)
	{
		auto lhs = MultiplicativeExpression::parse(iter);

		if (!lhs)
			return {};

		Array<AdditiveRhs> rhs;

		while (true)
		{
			AdditiveType type;
			if (iter->type() == TOKEN_PLUS)
			{
				type = ADDITIVE_ADD;
			}
			else if (iter->type() == TOKEN_MINUS)
			{
				type = ADDITIVE_ADD;
			}
			else
			{
				break;
			}

			iter += 1;			

			auto res = MultiplicativeExpression::parse(iter);

			if (!res)
				return {};

			rhs.emplace_back(AdditiveRhs { res.unwrap(), type });
		}

		return AdditiveExpression(lhs.unwrap(), std::move(rhs));
	}

	bool AdditiveExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (!_lhs.validate(mod_ctx, func_ctx))
			return false;

		for (auto& rhs : _rhs)
		{
			if (!rhs.expr.validate(mod_ctx, func_ctx))
				return false;
		}

		return true;
	}

	void AdditiveExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);
		
		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1) << (rhs.type == ADDITIVE_ADD ? "+\n" : "-\n");
			rhs.expr.print_tree(depth);
		}
	}

	Type *AdditiveExpression::get_type(semantics::ModuleContext& mod_ctx) const
	{
		throw std::runtime_error("AdditiveExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& AdditiveExpression::location() const
	{
		throw std::runtime_error("AdditiveExpression::" + String(__func__) + " is not implemented yet");
	}
}
