#include <warbler/syntax/expression/equality_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler::syntax
{
	EqualityExpression::EqualityExpression(Ptr<Expression>&& lhs, Array<EqualityRhs>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> EqualityExpression::parse(lexicon::Token& token)
	{
		auto lhs = RelationalExpression::parse(token);
		 
		if (!lhs)
			return {};

		Array<EqualityRhs> rhs;

		while (true)
		{
			bool should_break = false;

			EqualityType type;
			switch (token.type())
			{
				case lexicon::TokenType::Equals:
					type = EqualityType::Equals;
					break;

				case lexicon::TokenType::NotEquals:
					type = EqualityType::NotEquals;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			auto res = RelationalExpression::parse(token.next());

			if (!res)
				return {};

			rhs.emplace_back(EqualityRhs { res.unwrap(), type });
		}

		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new EqualityExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	// bool EqualityExpression::validate(semantics::SymbolTable& symbols)
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

	// void EqualityExpression::print_tree(u32 depth) const
	// {
	// 	if (_rhs.size() > 0)
	// 		depth += 1;

	// 	_lhs->print_tree(depth);

	// 	for (const auto& rhs : _rhs)
	// 	{
	// 		print_branch(depth - 1, rhs.type == EqualityType::Equals ? "==" : "!=");
	// 		rhs.expr->print_tree(depth);
	// 	}
	// }

	// Type *EqualityExpression::get_type()
	// {
	// 	throw std::runtime_error("EqualityExpression::" + String(__func__) + " is not implemented yet");
	// }

	// const lexicon::Token& EqualityExpression::token() const
	// {
	// 	throw std::runtime_error("EqualityExpression::" + String(__func__) + " is not implemented yet");
	// }
}
