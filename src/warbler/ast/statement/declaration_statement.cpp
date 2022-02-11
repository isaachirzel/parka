#include <warbler/ast/statement/declaration_statement.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	DeclarationStatement::DeclarationStatement(Declaration&& declaration, Ptr<Expression>&& value) :
	_declaration(std::move(declaration)),
	_value(std::move(value))
	{}

	Result<DeclarationStatement> DeclarationStatement::parse(TokenIterator& iter)
	{		
		iter += 1;

		auto declaration = Declaration::parse(iter);

		if (!declaration)
			return declaration.error();

		if (iter->type() != TOKEN_ASSIGN)
		{
			parse_error(iter, "expected '=' after declaration");
			return ERROR_ARGUMENT;
		}

		iter += 1;

		auto value = Expression::parse(iter);

		if (!value)
			return value.error();

		if (iter->type() != TOKEN_SEMICOLON)
		{
			parse_error(iter, "expected ';' after declaration");
			return ERROR_ARGUMENT;
		}

		iter += 1;

		return DeclarationStatement { declaration.unwrap(), value.unwrap() };
	}

	bool DeclarationStatement::validate(semantics::ModuleContext& context)
	{
		return _declaration.validate(context) && !_value->validate(context);
	}

	void DeclarationStatement::print_tree(u32 depth) const
	{
		_declaration.print_tree(depth);
		std::cout << tree_branch(depth + 1) << "=\n";
		_value->print_tree(depth  + 2);
	}
}