#include <warbler/ast/type/type_definition.hpp>

#include <warbler/print.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/ast/type/struct.hpp>
#include <warbler/ast/type/enum.hpp>

namespace warbler::ast
{
	TypeDefinition::TypeDefinition(Identifier&& name, TypeDefinitionBody *body) :
	_name(std::move(name)),
	_body(body)
	{}

	TypeDefinition::TypeDefinition(TypeDefinition&& other) :
	_name(std::move(other._name)),
	_symbol(std::move(other._symbol)),
	_body(other._body)
	{
		other._body = nullptr;
	}

	TypeDefinition::~TypeDefinition()
	{
		delete _body;
	}

#pragma message("TODO: implement all type parsing")
	Result<TypeDefinition> TypeDefinition::parse(TokenIterator& iter)
	{
		iter += 1;

		auto name = Identifier::parse(iter);

		if (!name)
			return {};

		if (iter->type() != TOKEN_COLON)
		{
			parse_error(iter, "':' after typename specification");
			return {};
		}

		iter += 1;

		switch (iter->type())
		{
			case TOKEN_STRUCT:
			{
				auto struct_def = Struct::parse(iter);

				if (!struct_def)
					return {};

				return TypeDefinition { name.unwrap(), new Struct(struct_def.unwrap()) };
			}

			default:
				parse_error(iter, "typename, enum definition, or struct definition");
				return {};
		}

	}

	bool TypeDefinition::validate(semantics::ModuleContext& context)
	{
		return _body->validate(context);
	}

	const String& TypeDefinition::generate_symbol(semantics::ModuleContext& context)
	{
		usize size = context.name.size() + 1 + _name.text().size();

		_symbol.reserve(size);

		_symbol += context.name;
		_symbol += '@';
		_symbol += _name.text();

		return _symbol;
	}

	void TypeDefinition::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << "type\n";

		_name.print_tree(depth + 1);
		_body->print_tree(depth + 1);
	}

	TypeDefinition& TypeDefinition::operator=(TypeDefinition&& other)
	{
		new (this) auto(std::move(other));
		return *this;
	}
}