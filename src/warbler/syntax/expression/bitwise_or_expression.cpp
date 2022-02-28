#include <warbler/syntax/expression/bitwise_or_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	BitwiseOrExpression::BitwiseOrExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> BitwiseOrExpression::parse(lexicon::TokenIterator& iter)
	{
		auto lhs = BitwiseXorExpression::parse(iter);

		if (!lhs)
			return {};

		Array<Ptr<Expression>> rhs;

		while (iter->type() == lexicon::TokenType::Pipeline)
		{
			iter += 1;

			auto res = BitwiseXorExpression::parse(iter);
			
			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new  BitwiseOrExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	// bool BitwiseOrExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	// {
	// 	if (!_lhs->validate(mod_ctx, func_ctx))
	// 		return false;

	// 	for (auto& expr : _rhs)
	// 	{
	// 		if (!expr->validate(mod_ctx, func_ctx))
	// 			return false;
	// 	}

	// 	return true;
	// }

	void BitwiseOrExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs->print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			print_branch(depth - 1, "|");
			rhs->print_tree(depth);
		}
	}

	Type *BitwiseOrExpression::get_type()
	{
		throw not_implemented();
	}

	const source::Location& BitwiseOrExpression::location() const
	{
		throw not_implemented();
	}
}
