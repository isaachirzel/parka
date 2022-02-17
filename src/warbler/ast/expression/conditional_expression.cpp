#include <warbler/ast/expression/conditional_expression.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/type/type.hpp>

namespace warbler::ast
{
	ConditionalRhs::ConditionalRhs(ConditionalExpression&& true_case, ConditionalExpression&& false_case) :
	true_case(std::move(true_case)),
	false_case(std::move(false_case))
	{}

	ConditionalExpression::ConditionalExpression(BooleanOrExpression&& lhs) :
	_lhs(std::move(lhs)),
	_rhs()
	{}

	ConditionalExpression::ConditionalExpression(BooleanOrExpression&& lhs, ConditionalRhs&& rhs) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs))
	{}

	Result<ConditionalExpression> ConditionalExpression::parse(TokenIterator& iter)
	{
		auto lhs = BooleanOrExpression::parse(iter);

		if (!lhs)
			return {};

		if (iter->type() != TOKEN_THEN)
			return ConditionalExpression { lhs.unwrap() };

		iter += 1;

		auto true_case = BooleanOrExpression::parse(iter);

		if (!true_case)
			return {};

		if (iter->type() != TOKEN_ELSE)
		{
			error_out(iter) << "expected 'else' for false case of conditional expression but got '" << *iter << '\'';
			error_highlight(iter);
			return {};
		}

		iter += 1;

		auto false_case = ConditionalExpression::parse(iter);

		if (!false_case)
			return {};

		return ConditionalExpression(lhs.unwrap(), ConditionalRhs { true_case.unwrap(), false_case.unwrap() });
	}

	bool ConditionalExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (!_lhs.validate(mod_ctx, func_ctx))
			return false;

		if (_rhs)
		{
			if (!_rhs->true_case.validate(mod_ctx, func_ctx) || !_rhs->false_case.validate(mod_ctx, func_ctx))
				return false;

			auto *true_type = _rhs->true_case.get_type(mod_ctx);
			auto *false_type = _rhs->false_case.get_type(mod_ctx);

			if (true_type != false_type)
			{
				#pragma message("TODO: implement type checking that allows for implicitly castable types")
				print_error(_rhs->false_case.location(), "type of false case is '" + false_type->name().text() + "', which is incompatible with true case type '" + true_type->name().text() + "'");
				print_note(_rhs->true_case.location(), "true case defined here");
				return false;
			}
		}

		return true;
	}

	Type *ConditionalExpression::get_type(semantics::ModuleContext& mod_ctx) const
	{
		return _rhs
			? _rhs->true_case.get_type(mod_ctx)
			: _lhs.get_type(mod_ctx);
	}

	void ConditionalExpression::print_tree(u32 depth) const
	{
		_lhs.print_tree(depth);

		if (_rhs)
		{
			std::cout << tree_branch(depth + 1) << "?\n";
			_rhs->true_case.print_tree(depth + 2);

			std::cout << tree_branch(depth + 1) << ":\n";
			_rhs->false_case.print_tree(depth + 2);
		}
	}
}
