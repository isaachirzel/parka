#include <warbler/ast/expression/shift_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler::ast
{
	ShiftExpression::ShiftExpression(AdditiveExpression&& lhs, std::vector<ShiftRhs>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<ShiftExpression> ShiftExpression::parse(TokenIterator& iter)
	{
		auto lhs = AdditiveExpression::parse(iter);

		if (!lhs)
			return {};

		std::vector<ShiftRhs> rhs;

		while (true)
		{
			bool should_break = false;
			ShiftType type;

			switch (iter->type())
			{
				case TOKEN_LSHIFT:
					type = SHIFT_LEFT;
					break;

				case TOKEN_RSHIFT:
					type = SHIFT_RIGHT;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;
			
			iter += 1;

			auto res = AdditiveExpression::parse(iter);

			if (!res)
				return {};

			rhs.emplace_back(ShiftRhs { res.unwrap(), type });
		}
		
		return ShiftExpression(lhs.unwrap(), std::move(rhs));
	}

	bool ShiftExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
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

	void ShiftExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			const char *symbol = rhs.type == SHIFT_LEFT
				? "<<\n"
				: ">>\n";

			std::cout << tree_branch(depth - 1) << symbol;
			rhs.expr.print_tree(depth);
		}
	}

	Type *ShiftExpression::get_type(semantics::ModuleContext& mod_ctx) const
	{
		throw std::runtime_error("ShiftExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& ShiftExpression::location() const
	{
		throw std::runtime_error("ShiftExpression::" + String(__func__) + " is not implemented yet");
	}
}