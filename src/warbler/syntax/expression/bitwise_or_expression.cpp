#include <warbler/syntax/expression/bitwise_or_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	BitwiseOrExpression::BitwiseOrExpression(Expression&& lhs, Array<Expression>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Expression> BitwiseOrExpression::parse(lexicon::Token& token)
	{
		auto lhs = BitwiseXorExpression::parse(token);

		if (!lhs)
			return {};

		Array<Expression> rhs;

		while (token.type() == lexicon::TokenType::Pipeline)
		{
			auto res = BitwiseXorExpression::parse(token.next());
			
			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		if (rhs.empty())
			return lhs.unwrap();

		return Expression(BitwiseOrExpression(lhs.unwrap(), std::move(rhs)));
	}

	// bool BitwiseOrExpression::validate(semantics::Context& context)
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

	// void BitwiseOrExpression::print_tree(u32 depth) const
	// {
	// 	if (_rhs.size() > 0)
	// 		depth += 1;

	// 	_lhs->print_tree(depth);

	// 	for (const auto& rhs : _rhs)
	// 	{
	// 		print_branch(depth - 1, "|");
	// 		rhs->print_tree(depth);
	// 	}
	// }

	// Type *BitwiseOrExpression::get_type()
	// {
	// 	throw not_implemented();
	// }

	// const lexicon::Token& BitwiseOrExpression::token() const
	// {
	// 	throw not_implemented();
	// }
}
