#include <warbler/ast/expression/boolean_or_expression.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	BooleanOrExpression::BooleanOrExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> BooleanOrExpression::parse(TokenIterator& iter)
	{
		auto lhs = BooleanAndExpression::parse(iter);

		if (!lhs)
			return {};

		Array<Ptr<Expression>> rhs;

		while (iter->type() == TOKEN_BOOLEAN_OR)
		{
			iter += 1;

			auto res = BooleanAndExpression::parse(iter);

			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new BooleanOrExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	bool BooleanOrExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
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

	void BooleanOrExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs->print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth) << "||\n";
			rhs->print_tree(depth);
		}
	}

	Type *BooleanOrExpression::get_type()
	{

		throw std::runtime_error("BooleanOrExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& BooleanOrExpression::location() const
	{
		throw std::runtime_error("BooleanOrExpression::" + String(__func__) + " is not implemented yet");
	}
}
