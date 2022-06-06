#include <stdexcept>
#include <warbler/validator.hpp>
#include <warbler/util/print.hpp>

namespace warbler
{
	bool validate_unique_symbol(const Token& token, const String& symbol, GlobalSymbolTable& symbols)
	{
		auto *previous_declaration = symbols.find(symbol);

		if (previous_declaration)
		{
			print_error(token, "The symbol '" + symbol + "' is already in use.");
			// TODO: show previous declaration
			return false;
		}

		return true;
	}

	Result<TypeAnnotationContext> validate_type_annotation(const TypeAnnotationSyntax& syntax, GlobalSymbolTable& symbol_table)
	{
		auto name = syntax.name().text();
		auto *symbol = symbol_table.resolve(name);

		if (symbol == nullptr)	// couldn't find symbol in context tree
		{
			print_error(syntax.name(), "Type '" + name + "' does not exist in this scope");
			return {};
		}

		switch (symbol->type())
		{
			case GlobalSymbolType::Struct:
			case GlobalSymbolType::Primitive:
				break;

			default:
				print_error(syntax.name(), "Expected type name, found "
					+ get_symbol_type_name(symbol->type())
					+ " '" + name + "'");
				return {};
		}

		return TypeAnnotationContext(Array<bool>(), symbol->type(), symbol->index());
	}

	Result<MemberContext> validate_struct_member(const MemberSyntax& syntax, GlobalSymbolTable& globals, Array<String>& containing_types)
	{
		auto name = syntax.name().text();
		auto type_name = syntax.type().name().text();
		auto *symbol = globals.resolve(type_name);

		if (symbol != nullptr)
		{
			if (symbol->type() == GlobalSymbolType::Struct && symbol->is_not_yet_validated())
			{
				if (!validate_struct(symbol->struct_syntax(), globals, containing_types))
					return {};
			}
		}

		auto type_annotation = validate_type_annotation(syntax.type(), globals);

		if (!type_annotation)
			return {};

		return MemberContext(syntax.name().text(), type_annotation.unwrap(), syntax.is_public());
	}

	bool validate_struct(const StructSyntax& syntax, GlobalSymbolTable& symbols, Array<String>& containing_types)
	{
		auto identifier = syntax.name().text();
		auto symbol = symbols.get_symbol(identifier);
		bool success = true;

		// TODO: potentially have this return false immediately as it could cause false positives with the other previously declared symbol
		// Example: the containing types could be incorrectly flagged as an error due to same names
		if (!validate_unique_symbol(syntax.name(), symbol, symbols))
			success = false;

		containing_types.push_back(symbol);

		Table<MemberContext> members;

		for (const auto& member_syntax : syntax.members())
		{
			auto res = validate_struct_member(member_syntax, symbols, containing_types);

			if (!res)
				success = false;

			auto member = res.unwrap();
			auto previous_declaration = members.find(member.name);

			if (previous_declaration != members.end())
			{
				print_error(syntax.name(), "Member '" + member.name + "' is already declared in struct.");
				success = false;
				continue;
			}

			members.emplace(member.name, std::move(member));
		}

		containing_types.pop_back();

		auto& data = symbols.get(symbol);

		if (success)
		{
			auto index = symbols.add_validated_struct(StructContext(std::move(symbol), std::move(members)));

			data.validate(index);
		}
		else
		{
			data.invalidate();
		}

		return success;
	}

	Result<ParameterContext> validate_parameter(const ParameterSyntax& syntax, GlobalSymbolTable& globals, LocalSymbolTable& locals)
	{
		throw not_implemented();
	}

	Result<FunctionSignatureContext> validate_function_signature(const FunctionSignatureSyntax& syntax, GlobalSymbolTable& globals, LocalSymbolTable& locals)
	{
		auto success = true;

		Array<ParameterContext> parameters;

		for (const auto& parameter_syntax : syntax.parameters())
		{
			auto parameter = validate_parameter(parameter_syntax, globals, locals);

			if (!parameter)
			{
				success = false;
				continue;
			}

			parameters.emplace_back(parameter.unwrap());
		}

		Optional<TypeAnnotationContext> return_type;

		if (syntax.return_type().has_value())
		{
			auto res = validate_type_annotation(syntax.return_type().value(), globals);

			if (!res)
			{
				success = false;
			}
			else
			{
				return_type = res.unwrap();
			}
		}

		if (!success)
			return {};		

		return FunctionSignatureContext(std::move(parameters), std::move(return_type));
	}

	Result<BlockStatementContext> validate_block_statement(const BlockStatementSyntax& syntax, GlobalSymbolTable& globals, LocalSymbolTable& locals)
	{
		throw not_implemented();
	}

	bool validate_function(const FunctionSyntax& syntax, GlobalSymbolTable& globals)
	{
		auto name = syntax.name().text();
		auto symbol = globals.get_symbol(name);

		auto locals_res = LocalSymbolTable::generate(syntax);

		if (!locals_res)
			return {};

		auto locals = locals_res.unwrap();

		auto success = true;

		// TODO: potentially return false immediately as it could cause false positives with function signature of same name
		if (!validate_unique_symbol(syntax.name(), symbol, globals))
			success = false;

		auto signature = validate_function_signature(syntax.signature(), globals, locals);

		if (!signature)
			success = false;

		auto body = validate_block_statement(syntax.body(), globals, locals);

		if (!body)
			success = false;

		if (!success)
			return {};

		auto& data = globals.get(symbol);
		auto index = globals.add_validated_function(FunctionContext(std::move(symbol), signature.unwrap(), body.unwrap()));
		data.validate(index);
	}

	Result<ProgramContext> validate(const ProgramSyntax& syntax)
	{
		Array<String> containing_types;

		auto globals_res = GlobalSymbolTable::generate(syntax);
		
		if (!globals_res)
			return {};

		auto globals = globals_res.unwrap();

		bool success = true;

		for (auto& pair : globals)
		{
			const auto& symbol = pair.first;
			auto& data = pair.second;

			if (data.is_already_validated())
				continue;


			globals.set_scope_from_symbol(symbol);

			switch (data.type())
			{
				case GlobalSymbolType::Struct:
					success = success && validate_struct(data.struct_syntax(), globals, containing_types);
					break;

				default:
					break;
			}
		}		

		if (!success)
			return {};

		return ProgramContext(globals.take_structs(), globals.take_primitives());
	}
}
