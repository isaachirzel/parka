#include <warbler/ast/expression/bitwise_or_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	BitwiseOrExpression::BitwiseOrExpression(BitwiseXorExpression&& lhs, Array<BitwiseXorExpression>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<BitwiseOrExpression> BitwiseOrExpression::parse(TokenIterator& iter)
	{
		auto lhs = BitwiseXorExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		Array<BitwiseXorExpression> rhs;

		while (iter->type() == TOKEN_PIPELINE)
		{
			iter += 1;

			auto res = BitwiseXorExpression::parse(iter);
			
			if (res.has_error())
				return res.error();

			rhs.emplace_back(res.unwrap());
		}

		return BitwiseOrExpression(lhs.unwrap(), std::move(rhs));
	}

	bool BitwiseOrExpression::validate(semantics::ModuleContext& context)
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

	void BitwiseOrExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1) << "|\n";
			rhs.print_tree(depth);
		}
	}
}
