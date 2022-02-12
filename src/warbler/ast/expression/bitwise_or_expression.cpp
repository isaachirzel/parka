#include <warbler/ast/expression/bitwise_or_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	BitwiseOrExpression::BitwiseOrExpression(BitwiseXorExpression&& lhs, Array<BitwiseXorExpression>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<BitwiseOrExpression> BitwiseOrExpression::parse(TokenIterator& iter)
	{
		auto lhs = BitwiseXorExpression::parse(iter);

		if (!lhs)
			return {};

		Array<BitwiseXorExpression> rhs;

		while (iter->type() == TOKEN_PIPELINE)
		{
			iter += 1;

			auto res = BitwiseXorExpression::parse(iter);
			
			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		return BitwiseOrExpression(lhs.unwrap(), std::move(rhs));
	}

	bool BitwiseOrExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (!_lhs.validate(mod_ctx, func_ctx))
			return false;

		for (auto& expr : _rhs)
		{
			if (!expr.validate(mod_ctx, func_ctx))
				return false;
		}

		return true;
	}

	void BitwiseOrExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1) << "|\n";
			rhs.print_tree(depth);
		}
	}
}
