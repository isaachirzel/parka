#include <warbler/ast/expression/comparison_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler
{
	ComparisonExpression::ComparisonExpression(ShiftExpression&& lhs, std::vector<ComparisonRhs>&& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	Result<ComparisonExpression> ComparisonExpression::parse(TokenIterator& iter)
	{
		auto lhs = ShiftExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		std::vector<ComparisonRhs> rhs;

		while (true)
		{
			bool should_break = false;

			ComparisonType type;
			switch (iter->type())
			{
				case TOKEN_GREATER_THAN:
					type = COMPARISON_GREATER;
					break;

				case TOKEN_LESS_THAN:
					type = COMPARISON_LESS;
					break;

				case TOKEN_GREATER_OR_EQUAL:
					type = COMPARISON_GREATER_EQUAL;
					break;

				case TOKEN_LESS_OR_EQUAL:
					type = COMPARISON_LESS_EQUAL;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			iter += 1;

			auto res = ShiftExpression::parse(iter);

			if (res.has_error())
				return res.error();

			rhs.emplace_back(ComparisonRhs { res.unwrap(), type });
		}

		return ComparisonExpression(lhs.unwrap(), std::move(rhs));
	}

	void ComparisonExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1);

			switch (rhs.type)
			{
				case COMPARISON_GREATER:
					std::cout << ">\n";
					break;

				case COMPARISON_LESS:
					std::cout << "<\n";
					break;

				case COMPARISON_GREATER_EQUAL:
					std::cout << ">=\n";
					break;

				case COMPARISON_LESS_EQUAL:
					std::cout << "<=\n";
					break;

			}

			rhs.expr.print_tree(depth);
		}
	}
}