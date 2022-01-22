#include <warbler/ast/expression/shift_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler::ast
{
	ShiftExpression::ShiftExpression(AdditiveExpression&& lhs, std::vector<ShiftRhs>&& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	Result<ShiftExpression> ShiftExpression::parse(TokenIterator& iter)
	{
		auto lhs = AdditiveExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

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

			if (res.has_error())
				return res.error();

			rhs.emplace_back(ShiftRhs { res.unwrap(), type });
		}
		
		return ShiftExpression(lhs.unwrap(), std::move(rhs));
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
}