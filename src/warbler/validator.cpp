#include <stdexcept>
#include <warbler/validator.hpp>

#include <warbler/util/print.hpp>

namespace warbler
{
	// Result<ParameterContext> validate_parameter(const ParameterSyntax& syntax)
	// {
	// 	auto *previous_declaration = func_ctx.get_parameter(_name.text());

	// 	if (previous_declaration)
	// 	{
	// 		print_error(_name.token(), "parameter '" + _name.text() + "' is previously declared in function '" + func_ctx.name + "'");
	// 		print_note(previous_declaration->name().token(), "previous declaration is here");
	// 		return false;
	// 	}

	// 	func_ctx.parameters[_name.text()] = this;
	// 	_type.validate(mod_ctx);

	// 	return true;
	// }

	// Result<VariableContext> validate_variable(const VariableSyntax& syntax)
	// {
	// 	auto *previous_declaration = func_ctx.current_block().get_variable(_name.text());

	// 	if (previous_declaration)
	// 	{
	// 		print_error(_name.token(), "'" + _name.text() + "' is previously declared as a variable in scope");
	// 		print_note(previous_declaration->name().token(), "previous declaration here");
	// 		return false;
	// 	}

	// 	auto is_base_scope = func_ctx.blocks.size() == 1;

	// 	if (is_base_scope)
	// 	{
	// 		previous_declaration = func_ctx.get_parameter(_name.text());

	// 		if (previous_declaration)
	// 		{
	// 			print_error(_name.token(), "'" + _name.text() + "' is previously declared as a parameter in function '" + func_ctx.name + "'");
	// 			print_note(previous_declaration->name().token(), "previous declaration here");
	// 			return false;
	// 		}
	// 	}

	// 	func_ctx.current_block().variables[_name.text()] = this;
	// 	_type.validate(mod_ctx);eEEE

	// 	return true;
	// }

	Result<IdentifierContext> validate_identifier(const IdentifierSyntax& syntax, SymbolTable& symbol_table)
	{
		throw not_implemented();
	}

	Result<TypeContext> validate_type_definition(const TypeSyntax& syntax, SymbolTable& symbols, Array<String>& encapsulation);

	Result<TypeAnnotationContext> validate_member_type_annotation(const TypeAnnotationSyntax& syntax, SymbolTable& symbol_table, Array<String>& encapsulation)
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

		if (symbol_data.type() != SymbolType::Type)
		{
			print_error(syntax.base_type(), "Symbol '" + type_name + "' is not a type and cannot be used as such");
			return {};
		}


		if (!resolution.data().is_validated())
		{
			bool is_containing_type = false;

			for (const auto& containing_type : encapsulation)
			{
				if (resolution.symbol() == containing_type)
				{
					is_containing_type = true;
					break;
				}
			}

			if (!is_containing_type)
			{
				if (!validate_type_definition(symbol_data.type_syntax(), symbol_table, encapsulation))
					return {};
			}
		}

		for (const auto& previous_type_symbol : encapsulation)
		{
			if (previous_type_symbol == resolution.symbol())
			{
				// TODO: improve this error by printing parent type name
				print_error(syntax.base_type(), "The type '" + resolution.symbol() + "' may not be used as a member of type '" + encapsulation.back() + "' as it creates a recursive type. Try using a reference to avoid this.");
				return {};
			}
		}

		// TODO: update errors to be better

		switch (resolution.data().type())
		{
			case SymbolType::Type:
				return TypeAnnotationContext(ptr_mutability, resolution.data().index());
				break;

			case SymbolType::Function:
				print_error(syntax.base_type(), "expected type, found function '" + type_name +"'");
				return {};

			case SymbolType::Parameter:
				print_error(syntax.base_type(), "expected type, found parameter '" + type_name +"'");
				return {};

			case SymbolType::Variable:
				print_error(syntax.base_type(), "expected type, found variable '" + type_name +"'");
				return {};
		}
	}

	Result<StructContext> validate_struct(const StructSyntax& syntax, SymbolTable& symbol_table, Array<String>& encapsulation)
	{
		// TODO: pass in type name for better error messages
		Table<MemberContext> members;

		for (const auto& member_syntax : syntax.members())
		{
			auto member_name = member_syntax.name().token().text();
			const auto& previous_declaration = members.find(member_name);
			auto name_already_exists = previous_declaration != members.end();

			if (name_already_exists)
			{
				// TODO: Search for previous declaration syntax for better diagnostics
				print_error(member_syntax.name().token(), "Member '" + member_name + "' is already declared in struct.");
				return {};
			}

			auto type_annotation = validate_member_type_annotation(member_syntax.type(), symbol_table, encapsulation);

			if (!type_annotation)
				return {};

			auto key = member_name; // This is done as consuming the member name int MemberContext causes problem with the emplacement

			members.emplace(key, MemberContext(member_name, type_annotation.unwrap(), member_syntax.is_public()));
		}

		return StructContext(members);
	}

	Result<TypeContext> validate_type_definition(const TypeSyntax& syntax, SymbolTable& symbols, Array<String>& encapsulation)
	{
		switch (syntax.type())
		{
			case TypeDefinitionType::Struct:
			{
				const auto& struct_syntax = syntax.struct_syntax();
				auto symbol = symbols.get_symbol(syntax.name().token().text());

				encapsulation.push_back(symbol);

				auto context = validate_struct(struct_syntax, symbols, encapsulation);

				if (!context)
					return {};


				return TypeContext(std::move(symbol), context.unwrap());
			}

			case TypeDefinitionType::Primitive:
				throw not_implemented();
		}

		throw not_implemented();
	}

	bool validate_package(const PackageSyntax& syntax, SymbolTable& symbols)
	{
		symbols.push_package(syntax.name());

		Array<String> type_encapsulation;

		// validate types
		auto success = true;

		for (const auto& type : syntax.type_definitions())
		{
			auto res = validate_type_definition(type, symbols, type_encapsulation);

			type_encapsulation.clear();

			if (!res)
			{
				success = false;
				continue;
			}

			auto index = symbols.add_validated_type(res.unwrap());
		}

		symbols.pop_package();

		return success;
	}

	Result<ProgramContext> validate(const ProgramSyntax& syntax)
	{
		Array<TypeContext> types;

		SymbolTable symbols(types);


		auto success = true;

		if (!symbols.add_symbols(syntax))
			success = false;

		for (const auto& package : syntax.packages())
		{
			success = success && validate_package(package, symbols);
		}

		if (!success)
			return {};

		return ProgramContext(std::move(types));
	}
}
