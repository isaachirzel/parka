#include <warbler/ast/declaration.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Declaration::Declaration(bool is_mutable, Identifier&& name, Typename&& type) :
	_is_mutable(is_mutable),
	_name(std::move(name)),
	_type(std::move(type))
	{}

	Result<Declaration> Declaration::parse_parameter(TokenIterator& iter)
	{
		auto is_mutable = false;

		if (iter->type() == TOKEN_MUT)
		{
			is_mutable = true;
			iter += 1;
		}

		auto name = Identifier::parse(iter);

		if (!name)
			return name.error();

		if (iter->type() != TOKEN_COLON)
		{
			print_error(iter->location(), "parameters may not be declared without a type");
			return ERROR_ARGUMENT;
		}

		iter += 1;

		auto type = Typename::parse(iter);

		if (!type)
			return type.error();

		return Declaration { is_mutable, name.unwrap(), type.unwrap() };
	}

	Result<Declaration> Declaration::parse_variable(TokenIterator& iter)
	{
		auto is_mutable = false;

		if (iter->type() == TOKEN_MUT)
		{
			is_mutable = true;
			iter += 1;
		}

		auto name = Identifier::parse(iter);
		
		if (name.has_error())
			return name.error();

		auto type = Typename(iter->location());

		if (iter->type() == TOKEN_COLON)
		{
			iter += 1;

			auto res = Typename::parse(iter);

			if (!res)
				return res.error();

			type = res.unwrap();
		}

		return Declaration { is_mutable, name.unwrap(), std::move(type) };
	}

	bool Declaration::validate_parameter(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (func_ctx.contains_parameter(_name.text()))
		{
			print_error(_name.location(), "parameter '" + _name.text() + "' is previously declared in function '" + func_ctx.name + "'");
			return false;
		}

		return true;
	}

	bool Declaration::validate_variable(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (func_ctx.contains_parameter(_name.text()))
		{
			print_error(_name.location(), "'" + _name.text() + "' is previously declared as a parameter in function '" + func_ctx.name + "'");
			return false;
		}

		if (func_ctx.contains_variable(_name.text()))
		{
			print_error(_name.location(), "'" + _name.text() + "' is previously declared in function '" + func_ctx.name + "'");
			return false;
		}

		return true;
	}

	void Declaration::print_tree(u32 depth = 0) const
	{
		if (_is_mutable)
			std::cout << tree_branch(depth) << "mut\n";
	}
}
