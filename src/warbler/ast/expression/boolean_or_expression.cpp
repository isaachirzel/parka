#include <warbler/ast/expression/boolean_or_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler
{
	BooleanOrExpression::BooleanOrExpression(BooleanAndExpression&& lhs, std::vector<BooleanAndExpression>&& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	Result<BooleanOrExpression> BooleanOrExpression::parse(TokenIterator& iter)
	{
		auto lhs = BooleanAndExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		std::vector<BooleanAndExpression> rhs;

		while (iter->type() == TOKEN_BOOLEAN_OR)
		{
			iter += 1;

			auto res = BooleanAndExpression::parse(iter);

			if (res.has_error())
				return res.error();

			rhs.emplace_back(res.unwrap());
		}

		return ERROR_NONE;
	}

	void BooleanOrExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			print_tree_branch_symbol("||", depth - 1);
			rhs.print_tree(depth);
		}
	}
}
