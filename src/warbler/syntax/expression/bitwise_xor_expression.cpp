#include <warbler/syntax//expression/bitwise_xor_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	BitwiseXorExpression::BitwiseXorExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> BitwiseXorExpression::parse(lexicon::TokenIterator& iter)
	{
		auto lhs = BitwiseAndExpression::parse(iter);

		if (!lhs)
			return {};

		Array<Ptr<Expression>> rhs;

		while (iter->type() == lexicon::TOKEN_CARROT)
		{
			iter += 1;

			auto res = BitwiseAndExpression::parse(iter);
			
			if (!res)
				return {};

			rhs.emplace_back(res.unwrap());
		}

		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new BitwiseXorExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	bool BitwiseXorExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
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

	void BitwiseXorExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs->print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1) << "^\n";
			rhs->print_tree(depth);
		}
	}

	Type *BitwiseXorExpression::get_type()
	{
		throw std::runtime_error("BitwiseXorExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& BitwiseXorExpression::location() const
	{
		throw std::runtime_error("BitwiseXorExpression::" + String(__func__) + " is not implemented yet");
	}
}
