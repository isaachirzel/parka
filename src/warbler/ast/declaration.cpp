#include <warbler/ast/declaration.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Declaration::Declaration(Identifier&& name, Type&& type, bool is_mutable) :
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

		auto name = Identifier::parse(iter);

		if (!name)
			return {};

		if (iter->type() != TOKEN_COLON)
		{
			print_error(iter->location(), "parameters may not be declared without a type");
			return {};
		}

		iter += 1;

		auto type = Type::parse(iter);

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

		auto name = Identifier::parse(iter);
		
		if (!name)
			return {};

		auto type = Type();

		if (iter->type() == TOKEN_COLON)
		{
			iter += 1;

			auto res = Type::parse(iter);

			if (!res)
				return {};

			type = res.unwrap();
		}

		return Declaration { name.unwrap(), std::move(type), is_mutable };
	}

	bool Declaration::validate_parameter(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		auto *previous_declaration = func_ctx.get_parameter(_name.text());

		if (previous_declaration)
		{
			print_error(_name.location(), "parameter '" + _name.text() + "' is previously declared in function '" + func_ctx.name + "'");
			print_note(previous_declaration->name().location(), "previous declaration is here");
			return false;
		}

		func_ctx.parameters[_name.text()] = this;
		_type.validate(mod_ctx);

		return true;
	}

	bool Declaration::validate_variable(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		auto *previous_declaration = func_ctx.current_block().get_variable(_name.text());

		if (previous_declaration)
		{
			print_error(_name.location(), "'" + _name.text() + "' is previously declared as a variable in scope");
			print_note(previous_declaration->name().location(), "previous declaration here");
			return false;
		}

		auto is_base_scope = func_ctx.blocks.size() == 1;

		if (is_base_scope)
		{
			previous_declaration = func_ctx.get_parameter(_name.text());

			if (previous_declaration)
			{
				print_error(_name.location(), "'" + _name.text() + "' is previously declared as a parameter in function '" + func_ctx.name + "'");
				print_note(previous_declaration->name().location(), "previous declaration here");
				return false;
			}
		}

		func_ctx.current_block().variables[_name.text()] = this;
		_type.validate(mod_ctx);

		return true;
	}

	void Declaration::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth);

		if (_is_mutable)
			std::cout << "mut ";
		
		std::cout << _name.text() << ": " << (!_type.name().empty() ?  _type.name() : "<auto>") << '\n';
	}
}
