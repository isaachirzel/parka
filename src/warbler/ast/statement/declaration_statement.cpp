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

		auto declaration = Declaration::parse_variable(iter);

		if (!declaration)
			return {};

		if (iter->type() != TOKEN_ASSIGN)
		{
			parse_error(iter, "expected '=' after declaration");
			return {};
		}

		iter += 1;

		auto value = Expression::parse(iter);

		if (!value)
			return {};

		if (iter->type() != TOKEN_SEMICOLON)
		{
			parse_error(iter, "expected ';' after declaration");
			return {};
		}

		iter += 1;

		return DeclarationStatement { declaration.unwrap(), value.unwrap() };
	}

	bool DeclarationStatement::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (!_declaration.validate_variable(mod_ctx, func_ctx) && _value->validate(mod_ctx, func_ctx))
			return false;

		auto& decl_type = _declaration.type();

		if (!decl_type.is_auto())
		{
			auto *expr_type = _value->get_type();

			if (!decl_type.validate_cast_from(expr_type))
				return false;
		}

		return true;
	}

	void DeclarationStatement::print_tree(u32 depth) const
	{
		_declaration.print_tree(depth);
		std::cout << tree_branch(depth + 1) << "=\n";
		_value->print_tree(depth  + 2);
	}
}