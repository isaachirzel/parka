#include <warbler/syntax/expression/relational_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	RelationalExpression::RelationalExpression(Ptr<Expression>&& lhs, Array<RelationalRhs>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> RelationalExpression::parse(lexicon::Token& token)
	{
		auto lhs = ShiftExpression::parse(token);

		if (!lhs)
			return {};

		Array<RelationalRhs> rhs;

		while (true)
		{
			bool should_break = false;

			RelationalType type;
			switch (token.type())
			{
				case lexicon::TokenType::GreaterThan:
					type = RelationalType::GreaterThan;
					break;

				case lexicon::TokenType::LessThan:
					type = RelationalType::LessThan;
					break;

				case lexicon::TokenType::GreaterThanOrEqualTo:
					type = RelationalType::GreaterThanOrEqualTo;
					break;

				case lexicon::TokenType::LessThanOrEqualTo:
					type = RelationalType::LessThanOrEqualTo;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			auto res = ShiftExpression::parse(token.next());

			if (!res)
				return {};

			rhs.emplace_back(RelationalRhs { res.unwrap(), type });
		}

		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new RelationalExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	// bool RelationalExpression::validate(semantics::Context& context)
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

	// void RelationalExpression::print_tree(u32 depth) const
	// {
	// 	if (_rhs.size() > 0)
	// 		depth += 1;

	// 	_lhs->print_tree(depth);

	// 	for (const auto& rhs : _rhs)
	// 	{
	// 		switch (rhs.type)
	// 		{
	// 			case RelationalType::GreaterThan:
	// 				print_branch(depth - 1, ">");
	// 				break;

	// 			case RelationalType::LessThan:
	// 				print_branch(depth - 1, "<");
	// 				break;

	// 			case RelationalType::GreaterThanOrEqualTo:
	// 				print_branch(depth - 1, ">=");
	// 				break;

	// 			case RelationalType::LessThanOrEqualTo:
	// 				print_branch(depth - 1, "<=");
	// 				break;

	// 		}

	// 		rhs.expr->print_tree(depth);
	// 	}
	// }

	// Type *RelationalExpression::get_type()
	// {
	// 	throw std::runtime_error("RelationExpression::" + String(__func__) + " is not implemented yet");
	// }

	// const lexicon::Token& RelationalExpression::token() const
	// {
	// 	if (!_rhs.empty())
	// 	{
	// 		return _lhs->token();
	// 	}
	// 	else
	// 	{
	// 		return _lhs->token() + _rhs.back().expr->token();
	// 	}
	// }
}