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

	Result<TypeAnnotationContext> validate_type_annotation(const TypeAnnotationSyntax& syntax, SymbolTable& symbol_table)
	{
		// TODO: pointer validation
		Array<bool> ptr_mutability;
		auto type_name = syntax.base_type().text();
		auto symbol = symbol_table.resolve("", type_name);

		if (!symbol)	// couldn't find symbol in context tree
		{
			print_error(syntax.base_type(), "type '" + type_name + "' does not exist in this scope");
			return {};
		}

		// TODO: update errors to be better

		switch (symbol->type())
		{
			case SymbolType::Type:
				return TypeAnnotationContext(ptr_mutability, symbol->index());
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

	Result<StructContext> validate_struct(const StructSyntax& syntax, SymbolTable& symbol_table)
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

			auto type_annotation = validate_type_annotation(member_syntax.type(), symbol_table);

			if (!type_annotation)
				return {};

			members.emplace(member_name, MemberContext(member_name, type_annotation.unwrap(), member_syntax.is_public()));
		}

		return StructContext(members);
	}

	Result<TypeContext> validate_type_definition(const TypeSyntax& syntax, SymbolTable& symbol_table, Array<String>& encapsulation_stack)
	{
		switch (syntax.type())
		{
			case TypeDefinitionType::Struct:
			{
				const auto& struct_syntax = syntax.struct_syntax();
				auto context = validate_struct(struct_syntax, symbol_table);

				if (!context)
					return {};

				auto symbol = syntax.name().token().text();

				return TypeContext(std::move(symbol), context.unwrap());
			}

			case TypeDefinitionType::Primitive:
				throw not_implemented();
				break;
		}

		throw not_implemented();
	}

	bool validate_package(const PackageSyntax& syntax, SymbolTable& symbols)
	{
		auto package = syntax.name();

		Array<String> encapsulation_stack;

		// validate types
		auto success = true;

		for (const auto& type : syntax.type_definitions())
		{
			auto res = validate_type_definition(type, symbols, encapsulation_stack);

			if (!res)
				return success = false;

			encapsulation_stack.clear();

			auto index = symbols.add_validated_type(res.unwrap());
			
		}

		return success;
	}

	Result<ProgramContext> validate(const ProgramSyntax& syntax)
	{
		Array<TypeContext> types;

		SymbolTable symbols(types);

		if (!symbols.add_symbols(syntax))
			return {};

		auto success = true;

		for (const auto& package : syntax.packages())
		{
			success = success && validate_package(package, symbols);
		}

		if (!success)
			return {};

		return ProgramContext(std::move(types));
	}
}
