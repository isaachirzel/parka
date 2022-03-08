#include <warbler/syntax/expression/boolean_or_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	BooleanOrExpression::BooleanOrExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> BooleanOrExpression::parse(lexicon::Token& token)
	{
		auto lhs = BooleanAndExpression::parse(token);

		if (!lhs)
			return {};

		Array<Ptr<Expression>> rhs;

		while (token.type() == lexicon::TokenType::BooleanOr)
		{
			auto res = BooleanAndExpression::parse(token.next());

			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new BooleanOrExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	// bool BooleanOrExpression::validate(semantics::Context& context)
	// {
	// 	if (!_lhs->validate(mod_ctx, func_ctx))
	// 		return false;

	// 	for (auto& expr : _rhs)
	// 	{
	// 		if (!expr->validate(mod_ctx, func_ctx))
	// 			return false;
	// 	}

	// 	return true;
	// // }

	// void BooleanOrExpression::print_tree(u32 depth) const
	// {
	// 	if (_rhs.size() > 0)
	// 		depth += 1;

	// 	_lhs->print_tree(depth);

	// 	for (const auto& rhs : _rhs)
	// 	{
	// 		print_branch(depth - 1, "||");
	// 		rhs->print_tree(depth);
	// 	}
	// }

	// Type *BooleanOrExpression::get_type()
	// {
	// 	throw not_implemented();
	// }

	// const lexicon::Token& BooleanOrExpression::token() const
	// {
	// 	throw not_implemented();
	// }
}
