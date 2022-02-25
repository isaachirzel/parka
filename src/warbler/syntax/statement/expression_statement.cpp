#include <warbler/syntax/statement/expression_statement.hpp>

// standard headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	ExpressionStatement::ExpressionStatement(Ptr<Expression>&& expression) :
	_expression(std::move(expression))
	{}

	Result<ExpressionStatement> ExpressionStatement::parse(lexicon::TokenIterator& iter)
	{
		auto expression = Expression::parse(iter);

		if (!expression)
			return {};

		if (iter->type() != lexicon::TOKEN_SEMICOLON)
		{
			print_parse_error(iter, "expected ';' after expression");
			return {};
		}

		iter += 1;

		return ExpressionStatement { expression.unwrap() };
	}

	bool ExpressionStatement::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		return _expression->validate(mod_ctx, func_ctx);
	}

	void ExpressionStatement::print_tree(u32 depth) const
	{
		_expression->print_tree(depth);
	}
}
