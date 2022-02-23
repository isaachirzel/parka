#include <warbler/syntax//expression/conditional_expression.hpp>

// local headers
#include <warbler/util/print.hpp>
#include <warbler/syntax//expression/expression.hpp>
#include <warbler/syntax//type/type_definition.hpp>

namespace warbler::syntax
{
	ConditionalExpression::ConditionalExpression(Ptr<Expression>&& lhs) :
	_lhs(std::move(lhs))
	{}

	ConditionalExpression::ConditionalExpression(Ptr<Expression>&& lhs, Ptr<Expression>&& true_case, Ptr<Expression>&& false_case) :
	_lhs(std::move(lhs)),
	_true_case(std::move(true_case)),
	_false_case(std::move(false_case))
	{}

	Result<Ptr<Expression>> ConditionalExpression::parse(TokenIterator& iter)
	{
		auto lhs = BooleanOrExpression::parse(iter);

		if (!lhs)
			return {};

		if (iter->type() != TOKEN_THEN)
			return lhs.unwrap();

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

		auto *ptr = new ConditionalExpression(lhs.unwrap(), true_case.unwrap(), false_case.unwrap());

		return Ptr<Expression>(ptr);
	}

	bool ConditionalExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (!_lhs->validate(mod_ctx, func_ctx))
			return false;

		if (_true_case)
		{
			if (!_true_case->validate(mod_ctx, func_ctx) || !_false_case->validate(mod_ctx, func_ctx))
				return false;

			auto *true_type = _true_case->get_type();
			auto *false_type = _false_case->get_type();

			if (true_type != false_type)
			{
				#pragma message("TODO: implement type checking that allows for implicitly castable types")

				print_error(_false_case->location(), "type of false case is '" + false_type->text() + "', which is incompatible with true case type '" + true_type->text() + "'");
				print_note(_true_case->location(), "true case defined here");

				return false;
			}
		}

		return true;
	}

	void ConditionalExpression::print_tree(u32 depth) const
	{
		_lhs->print_tree(depth);

		if (_true_case)
		{
			std::cout << tree_branch(depth + 1) << "?\n";
			_true_case->print_tree(depth + 2);

			std::cout << tree_branch(depth + 1) << ":\n";
			_false_case->print_tree(depth + 2);
		}
	}

	Type *ConditionalExpression::get_type()
	{
		return _true_case
			? _true_case->get_type()
			: _lhs->get_type();
	}

	const Location& ConditionalExpression::location() const
	{
		throw std::runtime_error("ConditionalExpression::" + String(__func__) + " is not implemented yet");
	}
}
