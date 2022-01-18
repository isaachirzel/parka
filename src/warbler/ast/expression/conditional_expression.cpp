#include <warbler/ast/expression/conditional_expression.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/expression.hpp>

// standard headers
#include <stdexcept>

namespace warbler
{
	ConditionalRhs::ConditionalRhs(BooleanOrExpression&& true_case, ConditionalExpression&& false_case) :
	true_case(true_case),
	false_case(false_case)
	{}

	ConditionalExpression::ConditionalExpression(BooleanOrExpression&& lhs) :
	_lhs(lhs),
	_rhs(nullptr)
	{}

	ConditionalExpression::ConditionalExpression(BooleanOrExpression&& lhs, ConditionalRhs&& rhs) :
	_lhs(lhs),
	_rhs(new ConditionalRhs(rhs))
	{}

	ConditionalExpression::ConditionalExpression(ConditionalExpression&& other) :
	_lhs(std::move(other._lhs)),
	_rhs(other._rhs)
	{
		other._rhs = nullptr;
	}

	ConditionalExpression::ConditionalExpression(const ConditionalExpression& other) :
	_lhs(other._lhs)
	{
		if (other._rhs != nullptr)
		{
			_rhs = new ConditionalRhs(*other._rhs);
		}
		else
		{
			_rhs = nullptr;
		}
	}

	ConditionalExpression::~ConditionalExpression()
	{
		delete _rhs;
	}

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
			error_out(iter) << "expected 'else' for false case of conditional expression but got '" << *iter << '\'' << token_error(iter) << std::endl;
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

		if (_rhs != NULL)
		{
			std::cout << tree_branch(depth + 1) << "?\n";
			_rhs->true_case.print_tree(depth + 2);

			std::cout << tree_branch(depth + 1) << ":\n";
			_rhs->false_case.print_tree(depth + 2);
		}
	}

	ConditionalExpression& ConditionalExpression::operator=(ConditionalExpression&& other)
	{
		new(this) auto(other);
		return *this;
	}

	ConditionalExpression& ConditionalExpression::operator=(const ConditionalExpression& other)
	{
		new(this) auto(other);
		return *this;
	}
}
