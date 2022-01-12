#include <warbler/ast/expression/multiplicative_expression.hpp>

// local includes
#include <warbler/print.hpp>

namespace warbler
{
	MultiplicativeExpression::MultiplicativeExpression(PrimaryExpression&& lhs, std::vector<MultiplicativeRhs>&& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	Result<MultiplicativeExpression> MultiplicativeExpression::parse(TokenIterator& iter)
	{
		auto lhs = PrimaryExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		std::vector<MultiplicativeRhs> rhs;

		while (true)
		{
			bool should_break = false;
			MultiplicativeType type;

			switch (iter->type())
			{
				case TOKEN_MODULUS:
					type = MULTIPLICATIVE_MODULUS;
					break;

				case TOKEN_ASTERISK:
					type = MULTIPLICATIVE_MULTIPLY;
					break;

				case TOKEN_SLASH:
					type = MULTIPLICATIVE_DIVIDE;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			iter += 1;

			auto res = PrimaryExpression::parse(iter);

			if (res.has_error())
				return res.error();

			rhs.emplace_back(MultiplicativeRhs { res.unwrap(), type });
		}

		return MultiplicativeExpression(lhs.unwrap(), std::move(rhs));
	}

	void MultiplicativeExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			print_branch(depth - 1);

			switch (rhs.type)
			{
				case MULTIPLICATIVE_MULTIPLY:
					puts("*");
					break;

				case MULTIPLICATIVE_DIVIDE:
					puts("/");
					break;

				case MULTIPLICATIVE_MODULUS:
					puts("%");
					break;
			}

			rhs.expr.print_tree(depth);
		}
	}
}
