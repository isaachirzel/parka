#include <warbler/syntax/expression/conditional_expression.hpp>

// local headers
#include <warbler/util/print.hpp>
#include <warbler/syntax/expression/expression.hpp>
#include <warbler/syntax/type/type_definition.hpp>

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

	Result<Ptr<Expression>> ConditionalExpression::parse(lexicon::TokenIterator& iter)
	{
		auto lhs = BooleanOrExpression::parse(iter);

		if (!lhs)
			return {};

		if (iter->type() != lexicon::TokenType::KeywordThen)
			return lhs.unwrap();

		iter += 1;

		auto true_case = BooleanOrExpression::parse(iter);

		if (!true_case)
			return {};

		if (iter->type() != lexicon::TokenType::KeywordElse)
		{
			print_parse_error(iter, "'else' or false case");
			return {};
		}

		iter += 1;

		auto false_case = ConditionalExpression::parse(iter);

		if (!false_case)
			return {};

		auto *ptr = new ConditionalExpression(lhs.unwrap(), true_case.unwrap(), false_case.unwrap());

		return Ptr<Expression>(ptr);
	}

	// bool ConditionalExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	// {
	// 	if (!_lhs->validate(mod_ctx, func_ctx))
	// 		return false;

	// 	if (_true_case)
	// 	{
	// 		if (!_true_case->validate(mod_ctx, func_ctx) || !_false_case->validate(mod_ctx, func_ctx))
	// 			return false;

	// 		auto *true_type = _true_case->get_type();
	// 		auto *false_type = _false_case->get_type();

	// 		if (true_type != false_type)
	// 		{
	// 			#pragma message("TODO: implement type checking that allows for implicitly castable types")

	// 			print_error(_false_case->location(), "type of false case is '" + false_type->location().text() + "', which is incompatible with true case type '" + true_type->location().text() + "'");
	// 			print_note(_true_case->location(), "true case defined here");

	// 			return false;
	// 		}
	// 	}

	// 	return true;
	// }

	void ConditionalExpression::print_tree(u32 depth) const
	{
		_lhs->print_tree(depth);

		if (_true_case)
		{
			print_branch(depth + 1, "then");
			_true_case->print_tree(depth + 2);
			print_branch(depth + 1, "else");
			_false_case->print_tree(depth + 2);
		}
	}

	// Type *ConditionalExpression::get_type()
	// {
	// 	return _true_case
	// 		? _true_case->get_type()
	// 		: _lhs->get_type();
	// }

	const source::Location& ConditionalExpression::location() const
	{
		throw not_implemented();
	}
}
