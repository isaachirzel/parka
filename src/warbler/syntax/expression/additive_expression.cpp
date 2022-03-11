#include <warbler/syntax/expression/additive_expression.hpp>

// local headers
#include <warbler/util/print.hpp>
#include <stdexcept>

namespace warbler::syntax
{
	AdditiveExpression::AdditiveExpression(Expression&& lhs, Array<AdditiveRhs>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Expression> AdditiveExpression::parse(lexicon::Token& token)
	{
		auto lhs = MultiplicativeExpression::parse(token);

		if (!lhs)
			return {};

		Array<AdditiveRhs> rhs;

		while (true)
		{
			AdditiveType type;
			if (token.type() == lexicon::TokenType::Plus)
			{
				type = AdditiveType::Add;
			}
			else if (token.type() == lexicon::TokenType::Minus)
			{
				type = AdditiveType::Add;
			}
			else
			{
				break;
			}

			auto res = MultiplicativeExpression::parse(token.next());

			if (!res)
				return {};

			rhs.emplace_back(AdditiveRhs { res.unwrap(), type });
		}

		if (rhs.empty())
			return lhs.unwrap();

		return Expression(AdditiveExpression {lhs.unwrap(), std::move(rhs) });
	}

	// bool AdditiveExpression::validate(semantics::Context& context)
	// {
	// 	if (!_lhs->validate(mod_ctx, func_ctx))
	// 		return false;

	// 	for (auto& rhs : _rhs)
	// 	{
	// 		if (!rhs.expr->validate(mod_ctx, func_ctx))
	// 			return false;
	// 	}

	// 	return true;
	// }

	// void AdditiveExpression::print_tree(u32 depth) const
	// {
	// 	if (_rhs.size() > 0)
	// 		depth += 1;

	// 	_lhs->print_tree(depth);
		
	// 	for (const auto& rhs : _rhs)
	// 	{
	// 		print_branch(depth - 1, rhs.type == AdditiveType::Add ? "+" : "-");
	// 		rhs.expr->print_tree(depth);
	// 	}
	// }

	// Type *AdditiveExpression::get_type()
	// {
	// 	throw std::runtime_error("AdditiveExpression::" + String(__func__) + " is not implemented yet");
	// }

	// const lexicon::Token& AdditiveExpression::token() const
	// {
	// 	throw std::runtime_error("AdditiveExpression::" + String(__func__) + " is not implemented yet");
	// }
}
