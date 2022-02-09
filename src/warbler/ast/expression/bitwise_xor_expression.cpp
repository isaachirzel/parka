#include <warbler/ast/expression/bitwise_xor_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	BitwiseXorExpression::BitwiseXorExpression(BitwiseAndExpression&& lhs, Array<BitwiseAndExpression>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<BitwiseXorExpression> BitwiseXorExpression::parse(TokenIterator& iter)
	{
		auto lhs = BitwiseAndExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		Array<BitwiseAndExpression> rhs;

		while (iter->type() == TOKEN_CARROT)
		{
			iter += 1;

			auto res = BitwiseAndExpression::parse(iter);
			
			if (res.has_error())
				return res.error();

			rhs.emplace_back(res.unwrap());
		}

		return BitwiseXorExpression(lhs.unwrap(), std::move(rhs));
	}

	void BitwiseXorExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1) << "^\n";
			rhs.print_tree(depth);
		}
	}
}
