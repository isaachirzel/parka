#include <warbler/ast/expression/multiplicative_expression.hpp>

// local includes
#include <warbler/print.hpp>

namespace warbler::ast
{
	MultiplicativeExpression::MultiplicativeExpression(Ptr<Expression>&& lhs, Array<MultiplicativeRhs>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<MultiplicativeExpression> MultiplicativeExpression::parse(TokenIterator& iter)
	{
		auto lhs = PrefixExpression::parse(iter);

		if (!lhs)
			return {};

		Array<MultiplicativeRhs> rhs;

		while (true)
		{
			bool should_break = false;

			MultiplicativeType type;
			switch (iter->type())
			{
				case TOKEN_MODULUS:
					type = MULTIPLICATIVE_MODULUS;
					break;

				case TOKEN_ASTERISK:
					type = MULTIPLICATIVE_MULTIPLY;
					break;

				case TOKEN_SLASH:
					type = MULTIPLICATIVE_DIVIDE;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			iter += 1;

			auto res = PrefixExpression::parse(iter);

			if (!res)
				return {};

			rhs.emplace_back(MultiplicativeRhs { res.unwrap(), type });
		}

		return MultiplicativeExpression(lhs.unwrap(), std::move(rhs));
	}

	bool MultiplicativeExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (!_lhs->validate(mod_ctx, func_ctx))
			return false;

		for (auto& rhs : _rhs)
		{
			if (!rhs.expr->validate(mod_ctx, func_ctx))
				return false;
		}

		return true;
	}

	void MultiplicativeExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs->print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1);

			switch (rhs.type)
			{
				case MULTIPLICATIVE_MULTIPLY:
					std::cout << "*\n";
					break;

				case MULTIPLICATIVE_DIVIDE:
					std::cout << "/\n";
					break;

				case MULTIPLICATIVE_MODULUS:
					std::cout << "%\n";
					break;
			}

			rhs.expr->print_tree(depth);
		}
	}

	Typename *MultiplicativeExpression::get_type(semantics::ModuleContext& mod_ctx) const
	{
		throw std::runtime_error("MultiplicativeExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& MultiplicativeExpression::location() const
	{
		throw std::runtime_error("MultiplicativeExpression::" + String(__func__) + " is not implemented yet");
	}
}
