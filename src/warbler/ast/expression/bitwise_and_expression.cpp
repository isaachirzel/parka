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

		if (lhs.has_error())
			return lhs.error();

		Array<EqualityExpression> rhs;

		while (iter->type() == TOKEN_AMPERSAND)
		{
			iter += 1;

			auto res = EqualityExpression::parse(iter);

			if (res.has_error())
				return res.error();

			rhs.emplace_back(res.unwrap());
		}

		return BitwiseAndExpression(lhs.unwrap(), std::move(rhs));
	}

	bool BitwiseAndExpression::validate(semantics::Context& context)
	{
		if (!_lhs.validate(context))
			return false;

		for (auto& expr : _rhs)
		{
			if (!expr.validate(context))
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
}
