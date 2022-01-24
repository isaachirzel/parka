#include <warbler/ast/statement/declaration_statement.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	DeclarationStatement::DeclarationStatement(Identifier&& name, Typename&& type, ConditionalExpression&& value) :
	_name(name),
	_type(type),
	_value(value)
	{}

	Result<DeclarationStatement> DeclarationStatement::parse(TokenIterator& iter)
	{		
		iter += 1;

		auto name = Identifier::parse(iter);
		
		if (name.has_error())
			return name.error();

		auto type = Typename();
		if (iter->type() == TOKEN_COLON)
		{
			iter += 1;

			auto res = Typename::parse(iter);

			if (res.has_error())
				return res.error();

			type = res.unwrap();
		}

		if (iter->type() != TOKEN_ASSIGN)
		{
			parse_error(iter, "expected '=' after declaration");
			return ERROR_ARGUMENT;
		}

		iter += 1;

		auto value = ConditionalExpression::parse(iter);

		if (value.has_error())
			return value.error();

		if (iter->type() != TOKEN_SEMICOLON)
		{
			parse_error(iter, "expected ';'");
			return ERROR_ARGUMENT;
		}

		iter += 1;

		return DeclarationStatement(name.unwrap(), std::move(type), value.unwrap());
	}

	void DeclarationStatement::print_tree(u32 depth) const
	{
		_name.print_tree(depth);
		_type.print_tree(depth + 1);
		std::cout << tree_branch(depth + 1) << "=\n";
		_value.print_tree(depth  + 2);
	}
}