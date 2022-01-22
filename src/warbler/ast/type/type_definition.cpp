#include <warbler/ast/type/type_definition.hpp>

#include <warbler/print.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	TypeDefinition::TypeDefinition(Identifier&& name, Struct&& struct_def) :
	_name(name),
	_struct(struct_def),
	_type(DEFINITION_STRUCT)
	{}

	TypeDefinition::TypeDefinition(Identifier&& name, Enum&& enum_def) :
	_name(name),
	_enum(enum_def),
	_type(DEFINITION_ENUM)
	{}

	TypeDefinition::TypeDefinition(TypeDefinition&& other) :
	_name(other._name),
	_type(other._type)
	{
		switch (_type)
		{
			case DEFINITION_STRUCT:
				new (&_struct) auto(std::move(other._struct));
				break;

			case DEFINITION_ENUM:
				new(&_enum) auto(std::move(other._enum));
				break;
		}
	}

	TypeDefinition::TypeDefinition(const TypeDefinition& other) :
	_name(other._name),
	_type(other._type)
	{
		switch (_type)
		{
			case DEFINITION_STRUCT:
				new (&_struct) auto(other._struct);
				break;

			case DEFINITION_ENUM:
				new(&_enum) auto(other._enum);
				break;
		}
	}

	TypeDefinition::~TypeDefinition()
	{
		switch (_type)
		{
			case DEFINITION_STRUCT:
				_struct.~Struct();
				break;

			case DEFINITION_ENUM:
				_enum.~Enum();
				break;
		}
	}
#pragma message("TODO: implement all type parsing")
	Result<TypeDefinition> TypeDefinition::parse(TokenIterator& iter)
	{
		iter += 1;

		auto name = Identifier::parse(iter);

		if (!name)
			return name.error();

		if (iter->type() != TOKEN_COLON)
		{
			parse_error(iter, "':' after typename specification");
			return ERROR_ARGUMENT;
		}

		iter += 1;

		switch (iter->type())
		{
			case TOKEN_STRUCT:
			{
				auto struct_def = Struct::parse(iter);

				if (!struct_def)
					return struct_def.error();

				return TypeDefinition(name.unwrap(), struct_def.unwrap());
			}

			default:
				parse_error(iter, "typename, enum definition, or struct definition");
				return ERROR_ARGUMENT;
		}

	}

	void TypeDefinition::validate(const semantics::Context& context)
	{
	}

	void TypeDefinition::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << "type\n";
	}

	TypeDefinition& TypeDefinition::operator=(TypeDefinition&& other)
	{
		new(this) auto(other);
		return *this;
	}

	TypeDefinition& TypeDefinition::operator=(const TypeDefinition& other)
	{
		new(this) auto(other);
		return *this;
	}
}