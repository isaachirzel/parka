#include <warbler/ast/declaration.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Declaration::Declaration(Name&& name, Typename&& type, bool is_mutable) :
	_name(std::move(name)),
	_type(std::move(type)),
	_is_mutable(is_mutable)
	{}

	Result<Declaration> Declaration::parse_parameter(TokenIterator& iter)
	{
		auto is_mutable = false;

		if (iter->type() == TOKEN_MUT)
		{
			is_mutable = true;
			iter += 1;
		}

		auto name = Name::parse(iter);

		if (!name)
			return {};

		if (iter->type() != TOKEN_COLON)
		{
			print_error(iter->location(), "parameters may not be declared without a type");
			return {};
		}

		iter += 1;

		auto type = Typename::parse(iter);

		if (!type)
			return {};

		return Declaration { name.unwrap(), type.unwrap(), is_mutable };
	}

	Result<Declaration> Declaration::parse_variable(TokenIterator& iter)
	{
		auto is_mutable = false;

		if (iter->type() == TOKEN_MUT)
		{
			is_mutable = true;
			iter += 1;
		}

		auto name = Name::parse(iter);
		
		if (!name)
			return {};

		auto type = Typename();

		if (iter->type() == TOKEN_COLON)
		{
			iter += 1;

			auto res = Typename::parse(iter);

			if (!res)
				return {};

			type = res.unwrap();
		}

		return Declaration { name.unwrap(), std::move(type), is_mutable };
	}

	bool Declaration::validate_parameter(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (func_ctx.contains(_name.text()))
		{
			print_error(_name.location(), "parameter '" + _name.text() + "' is previously declared in function '" + func_ctx.name + "'");
			return false;
		}

		return true;
	}

	bool Declaration::validate_variable(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		if (func_ctx.contains(_name.text()))
		{
			print_error(_name.location(), "'" + _name.text() + "' is previously declared as a parameter in function '" + func_ctx.name + "'");
			return false;
		}

		for (auto *block : func_ctx.blocks)
		{
			if (block->contains(_name.text()))
			{
				print_error(_name.location(), "'" + _name.text() + "' is previously declared in function '" + func_ctx.name + "'");
				return false;
			}
		}

		return true;
	}

	void Declaration::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth);

		if (_is_mutable)
			std::cout << "mut ";
		
		std::cout << _name.text() << ": " << _type.name() << '\n';
	}
}
