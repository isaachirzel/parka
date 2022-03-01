#include <warbler/syntax/expression/shift_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler::syntax
{
	ShiftExpression::ShiftExpression(Ptr<Expression>&& lhs, Array<ShiftRhs>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> ShiftExpression::parse(lexicon::Token& token)
	{
		auto lhs = AdditiveExpression::parse(token.next());

		if (!lhs)
			return {};

		Array<ShiftRhs> rhs;

		while (true)
		{
			bool should_break = false;
			ShiftType type;

			switch (token.type())
			{
				case lexicon::TokenType::LeftBitShift:
					type = ShiftType::Left;
					break;

				case lexicon::TokenType::RightBitShift:
					type = ShiftType::Right;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;
			
			token.next();

			auto res = AdditiveExpression::parse(token.next());

			if (!res)
				return {};

			rhs.emplace_back(ShiftRhs { res.unwrap(), type });
		}
		
		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new ShiftExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	// bool ShiftExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
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

	void ShiftExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs->print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			const char *symbol = rhs.type == ShiftType::Left
				? "<<\n"
				: ">>\n";

			print_branch(depth - 1, symbol);
			rhs.expr->print_tree(depth);
		}
	}

	Type *ShiftExpression::get_type()
	{
		throw std::runtime_error("ShiftExpression::" + String(__func__) + " is not implemented yet");
	}

	const lexicon::Token& ShiftExpression::token() const
	{
		throw std::runtime_error("ShiftExpression::" + String(__func__) + " is not implemented yet");
	}
}