#include <warbler/syntax/expression/boolean_and_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	BooleanAndExpression::BooleanAndExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> BooleanAndExpression::parse(lexicon::TokenIterator& iter)
	{
		auto lhs = BitwiseOrExpression::parse(iter);

		if (!lhs)
			return {};

		Array<Ptr<Expression>> rhs;

		while (iter->type() == lexicon::TOKEN_BOOLEAN_AND)
		{
			iter += 1;

			auto res = BitwiseOrExpression::parse(iter);

			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new BooleanAndExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	bool BooleanAndExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (!_lhs->validate(mod_ctx, func_ctx))
			return false;

		for (auto& expr : _rhs)
		{
			if (!expr->validate(mod_ctx, func_ctx))
				return false;
		}

		return true;
	}

	void BooleanAndExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs->print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			print_branch(depth - 1, "&&");
			rhs->print_tree(depth);
		}
	}

	Type *BooleanAndExpression::get_type()
	{
		throw not_implemented();
	}

	const source::Location& BooleanAndExpression::location() const
	{
		throw not_implemented();
	}
}
