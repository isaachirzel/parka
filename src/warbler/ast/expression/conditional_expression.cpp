#include <warbler/ast/expression/conditional_expression.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler::ast
{
	ConditionalRhs::ConditionalRhs(BooleanOrExpression&& true_case, ConditionalExpression&& false_case) :
	true_case(std::move(true_case)),
	false_case(std::move(false_case))
	{}

	ConditionalExpression::ConditionalExpression(BooleanOrExpression&& lhs) :
	_lhs(std::move(lhs)),
	_rhs()
	{}

	ConditionalExpression::ConditionalExpression(BooleanOrExpression&& lhs, ConditionalRhs&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<ConditionalExpression> ConditionalExpression::parse(TokenIterator& iter)
	{
		auto lhs = BooleanOrExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		if (iter->type() != TOKEN_THEN)
			return ConditionalExpression(lhs.unwrap());

		iter += 1;

		auto true_case = BooleanOrExpression::parse(iter);

		if (true_case.has_error())
			return true_case.error();

		if (iter->type() != TOKEN_ELSE)
		{
			error_out(iter) << "expected 'else' for false case of conditional expression but got '" << *iter << '\'';
			error_highlight(iter);
			return ERROR_ARGUMENT;
		}

		iter += 1;

		auto false_case = ConditionalExpression::parse(iter);

		if (false_case.has_error())
			return false_case.error();

		return ConditionalExpression(lhs.unwrap(), ConditionalRhs { true_case.unwrap(), false_case.unwrap() });
	}

	void ConditionalExpression::print_tree(u32 depth) const
	{
		_lhs.print_tree(depth);

		if (_rhs)
		{
			std::cout << tree_branch(depth + 1) << "?\n";
			_rhs->true_case.print_tree(depth + 2);

			std::cout << tree_branch(depth + 1) << ":\n";
			_rhs->false_case.print_tree(depth + 2);
		}
	}
}
