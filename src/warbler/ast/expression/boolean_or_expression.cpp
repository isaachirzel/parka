#include <warbler/ast/expression/boolean_or_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	BooleanOrExpression::BooleanOrExpression(BooleanAndExpression&& lhs, Array<BooleanAndExpression>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<BooleanOrExpression> BooleanOrExpression::parse(TokenIterator& iter)
	{
		auto lhs = BooleanAndExpression::parse(iter);

		if (!lhs)
			return {};

		Array<BooleanAndExpression> rhs;

		while (iter->type() == TOKEN_BOOLEAN_OR)
		{
			iter += 1;

			auto res = BooleanAndExpression::parse(iter);

			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		return BooleanOrExpression(lhs.unwrap(), std::move(rhs));
	}

	bool BooleanOrExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
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

	void BooleanOrExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth) << "||\n";
			rhs.print_tree(depth);
		}
	}

	Type *BooleanOrExpression::get_type(semantics::ModuleContext& mod_ctx) const
	{
		throw std::runtime_error("BooleanOrExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& BooleanOrExpression::location() const
	{
		throw std::runtime_error("BooleanOrExpression::" + String(__func__) + " is not implemented yet");
	}
}
