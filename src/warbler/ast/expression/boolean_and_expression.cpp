#include <warbler/ast/expression/boolean_and_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	BooleanAndExpression::BooleanAndExpression(BitwiseOrExpression&& lhs, Array<BitwiseOrExpression>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<BooleanAndExpression> BooleanAndExpression::parse(TokenIterator& iter)
	{
		auto lhs = BitwiseOrExpression::parse(iter);

		if (!lhs)
			return {};

		Array<BitwiseOrExpression> rhs;

		while (iter->type() == TOKEN_BOOLEAN_AND)
		{
			iter += 1;

			auto res = BitwiseOrExpression::parse(iter);

			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		return BooleanAndExpression(lhs.unwrap(), std::move(rhs));
	}

	bool BooleanAndExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
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

	void BooleanAndExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1) << "&&\n";
			rhs.print_tree(depth);
		}
	}

	Type *BooleanAndExpression::get_type(semantics::ModuleContext& mod_ctx) const
	{
		throw std::runtime_error("BooleanAndExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& BooleanAndExpression::location() const
	{
		throw std::runtime_error("BooleanAndExpression::" + String(__func__) + " is not implemented yet");
	}
}
