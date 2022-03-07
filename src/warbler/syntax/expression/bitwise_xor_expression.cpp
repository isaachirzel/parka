#include <warbler/syntax/expression/bitwise_xor_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	BitwiseXorExpression::BitwiseXorExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> BitwiseXorExpression::parse(lexicon::Token& token)
	{
		auto lhs = BitwiseAndExpression::parse(token);

		if (!lhs)
			return {};

		Array<Ptr<Expression>> rhs;

		while (token.type() == lexicon::TokenType::Carrot)
		{
			auto res = BitwiseAndExpression::parse(token.next());
			
			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new BitwiseXorExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	// bool BitwiseXorExpression::validate(semantics::SymbolTable& symbols)
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

	// void BitwiseXorExpression::print_tree(u32 depth) const
	// {
	// 	if (_rhs.size() > 0)
	// 		depth += 1;

	// 	_lhs->print_tree(depth);

	// 	for (const auto& rhs : _rhs)
	// 	{
	// 		print_branch(depth - 1, "^");
	// 		rhs->print_tree(depth);
	// 	}
	// }

	// Type *BitwiseXorExpression::get_type()
	// {
	// 	throw not_implemented();
	// }

	// const lexicon::Token& BitwiseXorExpression::token() const
	// {
	// 	throw not_implemented();
	// }
}
