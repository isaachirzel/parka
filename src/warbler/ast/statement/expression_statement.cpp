#include <warbler/ast/statement/expression_statement.hpp>

// standard headers
#include <warbler/print.hpp>

namespace warbler
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
			error_out(iter) << "expected ';' after expression but got '" << *iter << '\'' << token_error(iter) << std::endl;
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
