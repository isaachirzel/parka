#include <warbler/syntax/statement/expression_statement.hpp>

// standard headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	ExpressionStatement::ExpressionStatement(Expression&& expression) :
	_expression(std::move(expression))
	{}

	Result<ExpressionStatement> ExpressionStatement::parse(lexicon::Token& token)
	{
		auto expression = Expression::parse(token.next());

		if (!expression)
			return {};

		if (token.type() != lexicon::TokenType::Semicolon)
		{
			print_parse_error(token, "expected ';' after expression");
			return {};
		}

		token.next();

		return ExpressionStatement { expression.unwrap() };
	}

	// bool ExpressionStatement::validate(semantics::Context& context)
	// {
	// 	return _expression->validate(mod_ctx, func_ctx);
	// }

	// void ExpressionStatement::print_tree(u32 depth) const
	// {
	// 	_expression->print_tree(depth);
	// }
}
