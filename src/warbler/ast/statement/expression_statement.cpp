#include <warbler/ast/statement/expression_statement.hpp>

// standard headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	ExpressionStatement::ExpressionStatement(Expression&& expression) :
	_expression(expression)
	{}

	Result<ExpressionStatement> ExpressionStatement::parse(TokenIterator& iter)
	{
		auto expression = Expression::parse(iter);

		if (expression.has_error())
			return expression.error();

		if (iter->type() != TOKEN_SEMICOLON)
		{
			parse_error(iter, "expected ';' after expression");
			return ERROR_ARGUMENT;
		}

		iter += 1;

		return ExpressionStatement(expression.unwrap());
	}

	void ExpressionStatement::print_tree(u32 depth) const
	{
		_expression.print_tree(depth);
	}
}
