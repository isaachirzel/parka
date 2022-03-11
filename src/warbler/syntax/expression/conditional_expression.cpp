#include <warbler/syntax/expression/conditional_expression.hpp>

// local headers
#include <warbler/util/print.hpp>
#include <warbler/syntax/expression/expression.hpp>
#include <warbler/syntax/type/type_definition.hpp>

namespace warbler::syntax
{
	ConditionalExpression::ConditionalExpression(Expression&& lhs) :
	_lhs(std::move(lhs))
	{}

	ConditionalExpression::ConditionalExpression(Expression&& lhs, Expression&& true_case, Expression&& false_case) :
	_lhs(std::move(lhs)),
	_true_case(std::move(true_case)),
	_false_case(std::move(false_case))
	{}

	Result<Expression> ConditionalExpression::parse(lexicon::Token& token)
	{
		auto lhs = BooleanOrExpression::parse(token);

		if (!lhs)
			return {};

		if (token.type() != lexicon::TokenType::KeywordThen)
			return lhs.unwrap();

		auto true_case = BooleanOrExpression::parse(token.next());

		if (!true_case)
			return {};

		if (token.type() != lexicon::TokenType::KeywordElse)
		{
			print_parse_error(token, "'else' or false case");
			return {};
		}

		auto false_case = ConditionalExpression::parse(token.next());

		if (!false_case)
			return {};

		return Expression(ConditionalExpression(lhs.unwrap(), true_case.unwrap(), false_case.unwrap()));
	}

	// bool ConditionalExpression::validate(semantics::Context& context)
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

	// 			print_error(_false_case->token(), "type of false case is '" + false_type->token().text() + "', which is incompatible with true case type '" + true_type->token().text() + "'");
	// 			print_note(_true_case->token(), "true case defined here");

	// 			return false;
	// 		}
	// 	}

	// 	return true;
	// }

	// void ConditionalExpression::print_tree(u32 depth) const
	// {
	// 	_lhs->print_tree(depth);

	// 	if (_true_case)
	// 	{
	// 		print_branch(depth + 1, "then");
	// 		_true_case->print_tree(depth + 2);
	// 		print_branch(depth + 1, "else");
	// 		_false_case->print_tree(depth + 2);
	// 	}
	// }

	// // Type *ConditionalExpression::get_type()
	// // {
	// // 	return _true_case
	// // 		? _true_case->get_type()
	// // 		: _lhs->get_type();
	// // }

	// const lexicon::Token& ConditionalExpression::token() const
	// {
	// 	throw not_implemented();
	// }
}
