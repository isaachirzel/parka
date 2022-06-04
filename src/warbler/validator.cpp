#include <stdexcept>
#include <warbler/validator.hpp>

#include <warbler/util/print.hpp>

namespace warbler
{
	Result<IdentifierContext> validate_identifier(const Token& syntax, SymbolTable& symbol_table)
	{
		throw not_implemented();
	}

	Result<TypeAnnotationContext> validate_member_type_annotation(const TypeAnnotationSyntax& syntax, SymbolTable& symbol_table, Array<String>& containing_types)
	{
		// TODO: pointer validation
		Array<bool> ptr_mutability;
		auto type_name = syntax.base_type().text();
		auto symbol_res = symbol_table.resolve(type_name);

		if (!symbol_res)	// couldn't find symbol in context tree
		{
			print_error(syntax.base_type(), "Type '" + type_name + "' does not exist in this scope");
			return {};
		}

		auto resolution = symbol_res.unwrap();
		auto& symbol_data = resolution.data();

		auto symbol_type = resolution.data().type();

		switch (symbol_type)
		{
			case SymbolType::Struct:
				// Check for recursive type members
				for (const auto& containing_type : containing_types)
				{
					if (resolution.symbol() == containing_type)
					{
						// TODO: improve this error by printing parent type name
						print_error(syntax.base_type(), "The type '" + resolution.symbol() + "' may not be used as a member of type '" + containing_types.back() + "' as it creates a recursive type. Try using a reference to avoid this.");
						return {};
					}
				}

				if (symbol_data.is_not_yet_validated())
				{
					// TODO: Add a flag to check if a type has failed validation as an invalid type getting used as a member of another type will cause it to be valdiated twice
					if (!validate_struct(symbol_data.struct_syntax(), symbol_table, containing_types))
						return {};
				}
				break;

			case SymbolType::Primitive:
				break;

			default:
				print_error(syntax.base_type(), "expected member type, found "
					+ get_symbol_type_name(resolution.data().type())
					+ " '" + type_name + "'");

				return {};
		}

		return TypeAnnotationContext(ptr_mutability, symbol_type, symbol_data.index());
	}

	bool validate_struct(const StructSyntax& syntax, SymbolTable& symbols, Array<String>& containing_types)
	{
		auto identifier = syntax.name().text();
		auto symbol = symbols.get_symbol(identifier);

		containing_types.push_back(symbol);

		Table<MemberContext> members;

		bool success = true;

		for (const auto& member_syntax : syntax.members())
		{
			// TODO: add validate_member function
			auto member_name = member_syntax.name().text();
			const auto& previous_declaration = members.find(member_name);
			auto name_already_exists = previous_declaration != members.end();

			if (name_already_exists)
			{
				// TODO: Search for previous declaration syntax for better diagnostics
				print_error(member_syntax.name(), "Member '" + member_name + "' is already declared in struct.");
				return {};
			}

			auto type_annotation = validate_member_type_annotation(member_syntax.type(), symbols, containing_types);

			if (!type_annotation)
			{
				success = false;
				continue;
			}

			auto key = member_name; // This is done as consuming the member name int MemberContext causes problem with the emplacement

			members.emplace(key, MemberContext(member_name, type_annotation.unwrap(), member_syntax.is_public()));
		}

		containing_types.pop_back();

		auto& data = symbols.get(symbol);

		if (success)
		{
			auto index = symbols.add_validated_type(StructContext(std::move(symbol), std::move(members)));

			data.validate(index);
		}
		else
		{
			data.invalidate();
		}

		return success;
	}

	Result<ProgramContext> validate(const ProgramSyntax& syntax)
	{
		Array<StructContext> structs;
		Array<PrimitiveContext> primitives;
		Array<String> containing_types;
		SymbolTable symbols(structs, primitives);

		if (!symbols.add_symbols(syntax))
			return {};

		bool success = true;

		for (auto& pair : symbols)
		{
			const auto& symbol = pair.first;
			auto& data = pair.second;

			if (data.is_already_validated())
				continue;


			symbols.set_scope_from_symbol(symbol);

			switch (data.type())
			{
				case SymbolType::Struct:
					success = success && validate_struct(data.struct_syntax(), symbols, containing_types);
					break;

				default:
					break;
			}
		}		

		if (!success)
			return {};

		return ProgramContext(std::move(structs), std::move(primitives));
	}
}
