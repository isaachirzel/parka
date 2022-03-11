#include <warbler/syntax/expression/multiplicative_expression.hpp>

// local includes
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	MultiplicativeExpression::MultiplicativeExpression(Expression&& lhs, Array<MultiplicativeRhs>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Expression> MultiplicativeExpression::parse(lexicon::Token& token)
	{
		auto lhs = PrefixExpression::parse(token);

		if (!lhs)
			return {};

		Array<MultiplicativeRhs> rhs;

		while (true)
		{
			bool should_break = false;

			MultiplicativeType type;
			switch (token.type())
			{
				case lexicon::TokenType::Modulus:
					type = MultiplicativeType::Modulus;
					break;

				case lexicon::TokenType::Asterisk:
					type = MultiplicativeType::Multiply;
					break;

				case lexicon::TokenType::Slash:
					type = MultiplicativeType::Divide;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			auto res = PrefixExpression::parse(token.next());

			if (!res)
				return {};

			rhs.emplace_back(MultiplicativeRhs { res.unwrap(), type });
		}

		if (rhs.empty())
			return lhs.unwrap();

		return Expression(MultiplicativeExpression(lhs.unwrap(), std::move(rhs)));
	}

	// bool MultiplicativeExpression::validate(semantics::Context& context)
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

	// void MultiplicativeExpression::print_tree(u32 depth) const
	// {
	// 	if (_rhs.size() > 0)
	// 		depth += 1;

	// 	_lhs->print_tree(depth);

	// 	for (const auto& rhs : _rhs)
	// 	{
	// 		switch (rhs.type)
	// 		{
	// 			case MultiplicativeType::Multiply:
	// 				print_branch(depth - 1, "*");
	// 				break;

	// 			case MultiplicativeType::Divide:
	// 				print_branch(depth - 1, "/");
	// 				break;

	// 			case MultiplicativeType::Modulus:
	// 				print_branch(depth - 1, "%");
	// 				break;
	// 		}

	// 		rhs.expr->print_tree(depth);
	// 	}
	// }

	// Type *MultiplicativeExpression::get_type()
	// {
	// 	throw std::runtime_error("MultiplicativeExpression::" + String(__func__) + " is not implemented yet");
	// }

	// const lexicon::Token& MultiplicativeExpression::token() const
	// {
	// 	throw std::runtime_error("MultiplicativeExpression::" + String(__func__) + " is not implemented yet");
	// }
}
