#include <warbler/ast/expression/boolean_and_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler
{
	BooleanAndExpression::BooleanAndExpression(BitwiseOrExpression&& lhs, std::vector<BitwiseOrExpression>&& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	Result<BooleanAndExpression> BooleanAndExpression::parse(TokenIterator& iter)
	{
		auto lhs = BitwiseOrExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		std::vector<BitwiseOrExpression> rhs;

		while (iter->type() == TOKEN_BOOLEAN_AND)
		{
			iter += 1;

			auto res = BitwiseOrExpression::parse(iter);

			if (res.has_error())
				return res.error();

			rhs.emplace_back(res.unwrap());
		}

		return BooleanAndExpression(lhs.unwrap(), std::move(rhs));
	}

	void BooleanAndExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			print_tree_branch_symbol("&&", depth - 1);
			rhs.print_tree(depth);
		}
	}
}
