#include <warbler/ast/statement/declaration_statement.hpp>

#include <warbler/print.hpp>

namespace warbler
{
	DeclarationStatement::DeclarationStatement(Identifier&& name, Typename&& type, Expression&& value) :
	_name(name),
	_type(type),
	_value(value)
	{}

	Result<DeclarationStatement> DeclarationStatement::parse(TokenIterator& iter)
	{		
		iter += 1;

		auto name = Identifier::parse(iter);
		
		auto type = iter->type() == TOKEN_COLON
			? Typename::parse(++iter)
			: Typename();

		if (iter->type() != TOKEN_EQUALS)
		{
			error_out(iter) << "expected '=' but got: " << *iter << std::endl;
			return ERROR_ARGUMENT;
		}

		auto value = Expression::parse(iter);

		if (iter->type() != TOKEN_SEMICOLON)
		{
			error_out(iter) << "expected ';' but got: " << *iter << std::endl;
			return ERROR_ARGUMENT;
		}

		return DeclarationStatement(name.unwrap(), type.unwrap(), value.unwrap());
	}

	void DeclarationStatement::print_tree(u32 depth) const
	{
		_name.print_tree(depth);

		print_tree_branch_symbol(":", depth);
		_type.print_tree(depth + 1);
		print_tree_branch_symbol("=", depth + 1);
		_value.print_tree(depth  + 2);
	}
}