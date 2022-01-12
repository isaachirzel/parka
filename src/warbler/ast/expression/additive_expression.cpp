#include <warbler/ast/expression/additive_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler
{
	AdditiveExpression::AdditiveExpression(MultiplicativeExpression&& lhs, std::vector<AdditiveRhs>&& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	Result<AdditiveExpression> AdditiveExpression::parse(TokenIterator& iter)
	{
		auto lhs = MultiplicativeExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		std::vector<AdditiveRhs> rhs;

		while (iter->type() == TOKEN_PLUS || iter->type() == TOKEN_MINUS)
		{
			auto type = iter->type() == TOKEN_PLUS
				? ADDITIVE_ADD
				: ADDITIVE_SUBTRACT;

			iter += 1;			

			auto res = MultiplicativeExpression::parse(iter);

			if (res.has_error())
				return res.error();

			rhs.emplace_back(AdditiveRhs { res.unwrap(), type });
		}

		return AdditiveExpression(lhs.unwrap(), std::move(rhs));
	}

	void AdditiveExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);
		
		for (const auto& rhs : _rhs)
		{
			
			print_branch(depth - 1);

			switch (rhs.type)
			{
				case ADDITIVE_ADD:
					puts("+");
					break;

				case ADDITIVE_SUBTRACT:
					puts("-");
					break;		
			}

			rhs.expr.print_tree(depth);
		}
	}
}
