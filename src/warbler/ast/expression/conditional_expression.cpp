#include <warbler/ast/expression/conditional_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler
{
	ConditionalExpression::ConditionalExpression(BooleanOrExpression&& lhs) :
	_lhs(lhs)
	{}

	Result<ConditionalExpression> ConditionalExpression::parse(TokenIterator& iter)
	{
		auto lhs = BooleanOrExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		return ConditionalExpression(lhs.unwrap());
	}

	void ConditionalExpression::print_tree(u32 depth)
	{
		_lhs.print_tree(depth);

		if (_type == CONDITIONAL_TERNARY)
		{
			throw std::runtime_error("ternary printing is not implemented yet");
		}
	}
}
