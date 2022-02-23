#include <warbler/ast/expression/bitwise_and_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler::ast
{
	BitwiseAndExpression::BitwiseAndExpression(EqualityExpression&& lhs, Array<EqualityExpression>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<BitwiseAndExpression> BitwiseAndExpression::parse(TokenIterator& iter)
	{
		auto lhs = EqualityExpression::parse(iter);

		if (!lhs)
			return {};

		Array<EqualityExpression> rhs;

		while (iter->type() == TOKEN_AMPERSAND)
		{
			iter += 1;

			auto res = EqualityExpression::parse(iter);

			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		return BitwiseAndExpression(lhs.unwrap(), std::move(rhs));
	}

	bool BitwiseAndExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
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

	void BitwiseAndExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1) << "&\n";
			rhs.print_tree(depth);
		}
	}

	Type *BitwiseAndExpression::get_type(semantics::ModuleContext& mod_ctx) const
	{
		throw std::runtime_error("BitwiseAndExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& BitwiseAndExpression::location() const
	{
		throw std::runtime_error("BitwiseAndExpression::" + String(__func__) + " is not implemented yet");
	}
}
