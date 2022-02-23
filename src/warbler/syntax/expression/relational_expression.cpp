#include <warbler/syntax//expression/relational_expression.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	RelationalExpression::RelationalExpression(Ptr<Expression>&& lhs, std::vector<RelationalRhs>&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<Ptr<Expression>> RelationalExpression::parse(TokenIterator& iter)
	{
		auto lhs = ShiftExpression::parse(iter);

		if (!lhs)
			return {};

		std::vector<RelationalRhs> rhs;

		while (true)
		{
			bool should_break = false;

			RelationalType type;
			switch (iter->type())
			{
				case TOKEN_GREATER_THAN:
					type = RELATIONAL_GREATER;
					break;

				case TOKEN_LESS_THAN:
					type = RELATIONAL_LESS;
					break;

				case TOKEN_GREATER_OR_EQUAL:
					type = RELATIONAL_GREATER_EQUAL;
					break;

				case TOKEN_LESS_OR_EQUAL:
					type = RELATIONAL_LESS_EQUAL;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			iter += 1;

			auto res = ShiftExpression::parse(iter);

			if (!res)
				return {};

			rhs.emplace_back(RelationalRhs { res.unwrap(), type });
		}

		if (rhs.empty())
			return lhs.unwrap();

		auto *ptr = new  RelationalExpression(lhs.unwrap(), std::move(rhs));

		return Ptr<Expression>(ptr);
	}

	bool RelationalExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
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

	void RelationalExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs->print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1);

			switch (rhs.type)
			{
				case RELATIONAL_GREATER:
					std::cout << ">\n";
					break;

				case RELATIONAL_LESS:
					std::cout << "<\n";
					break;

				case RELATIONAL_GREATER_EQUAL:
					std::cout << ">=\n";
					break;

				case RELATIONAL_LESS_EQUAL:
					std::cout << "<=\n";
					break;

			}

			rhs.expr->print_tree(depth);
		}
	}

	Type *RelationalExpression::get_type()
	{
		throw std::runtime_error("RelationExpression::" + String(__func__) + " is not implemented yet");
	}

	const Location& RelationalExpression::location() const
	{
		if (!_rhs.empty())
		{
			return _lhs->location();
		}
		else
		{
			return _lhs->location() + _rhs.back().expr->location();
		}
	}
}