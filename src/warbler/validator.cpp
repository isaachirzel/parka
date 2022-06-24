#include <stdexcept>
#include <warbler/validator.hpp>
#include <warbler/util/print.hpp>

namespace warbler
{
	Result<TypeAnnotationContext> validate_type_annotation(const TypeAnnotationSyntax& syntax, GlobalSymbolTable& symbol_table)
	{
		auto name = syntax.name().text();
		auto *symbol = symbol_table.resolve(name);

		if (symbol == nullptr)	// couldn't find symbol in context tree
		{
			print_error(syntax.name(), "Type '" + name + "' does not exist in this scope");
			return {};
		}

		AnnotationType type;

		switch (symbol->type())
		{
			case GlobalSymbolType::Struct:
				type = AnnotationType::Struct;
				break;

			case GlobalSymbolType::Primitive:
				type = AnnotationType::Primitive;
				break;

			default:
				print_error(syntax.name(), "Expected type name, found "
					+ get_symbol_type_name(symbol->type())
					+ " '" + name + "'");
				return {};
		}

		return TypeAnnotationContext(Array<bool>(), type, symbol->index());
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

		containing_types.push_back(symbol);

		Table<MemberContext> members;

		for (const auto& member_syntax : syntax.members())
		{
			auto res = validate_struct_member(member_syntax, symbols, containing_types);

			if (!res)
				success = false;

			auto member = res.unwrap();
			auto previous_declaration = members.find(member.name());

			if (previous_declaration != members.end())
			{
				print_error(syntax.name(), "Member '" + member.name() + "' is already declared in struct.");
				success = false;
				continue;
			}

			members.emplace(member.name(), std::move(member));
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
		auto type = validate_type_annotation(syntax.type(), globals);

		if (!type)
			return {};

		return ParameterContext(syntax.name().text(), type.unwrap(), syntax.is_mutable());
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

	Result<ExpressionContext> validate_constant(const ConstantSyntax& syntax)
	{
		switch (syntax.type())
		{
			case ConstantType::Character:
				return ExpressionContext(ConstantContext(syntax.character()));

			case ConstantType::StringLiteral:
				return ExpressionContext(ConstantContext(syntax.string()));

			case ConstantType::SignedInteger:
				return ExpressionContext(ConstantContext(syntax.integer()));

			case ConstantType::UnsignedInteger:
				return ExpressionContext(ConstantContext(syntax.uinteger()));

			case ConstantType::Float:
				return ExpressionContext(ConstantContext(syntax.floating()));

			case ConstantType::Boolean:
				return ExpressionContext(ConstantContext(syntax.boolean()));

			default:
				throw std::runtime_error("Invalid constant type");
		}
	}

	Result<ExpressionContext> validate_expression(const ExpressionSyntax& syntax, GlobalSymbolTable& globals, LocalSymbolTable& locals)
	{
		switch (syntax.type())
		{
			case ExpressionType::Constant:
				return validate_constant(syntax.constant());

			default:
				throw std::runtime_error("Validation of this type of expression is not implemented yet");
		}
	}

	Result<VariableContext> validate_variable(const VariableSyntax& syntax, GlobalSymbolTable& globals, LocalSymbolTable& locals)
	{
		auto name = syntax.name().text();

		if (syntax.is_auto_type())
		{
			return VariableContext(std::move(name), syntax.is_mutable());
		}

		auto type = validate_type_annotation(syntax.type(), globals);

		if (!type)
			return {};

		return VariableContext(std::move(name), type.unwrap(), syntax.is_mutable());
	}

	Result<DeclarationContext> validate_declaration_statement(const DeclarationSyntax& syntax, GlobalSymbolTable& globals, LocalSymbolTable& locals)
	{
		auto var_res = validate_variable(syntax.variable(), globals, locals);

		if (!var_res)
			return {};

		auto value_res = validate_expression(syntax.value(), globals, locals);
		
		if (!value_res)
			return {};

		auto var = var_res.unwrap();

		if (var.is_auto_type())
			return DeclarationContext(std::move(var), value_res.unwrap());

		auto value = value_res.unwrap();

		const auto& variable_type = var.type();
		auto expression_type = value.type_annotation();
	
		// TODO: Account for primitives

		if (variable_type.type() != expression_type.type())
		{
			// TODO: Add syntax hooks to context structs
			print_error(syntax.variable().name(), "Cannot assign between primitive and struct");
			return {};
		}


		switch (variable_type.type())
		{
			case AnnotationType::Struct:
			{
				auto is_not_same_type = variable_type.index() != expression_type.index();

				if (is_not_same_type)
				{
					auto lstruct = globals.get_struct(variable_type.index());
					auto rstruct = globals.get_struct(expression_type.index());

					print_error(syntax.variable().name(), "Cannot initialize variable of type '" + lstruct.symbol()
						+ "' with value of type '" + rstruct.symbol() + "'");
					return {};
				}
				break;
			}

			case AnnotationType::Primitive:
			{
				auto left = globals.get_primitive(variable_type.index());
				auto right = globals.get_primitive(variable_type.index());

				if (left.type() != right.type())
				{
					print_error(syntax.variable().name(), "Cannot assign variable of type '" + String(left.type_name())
						+ "' value of type '" + right.type_name() + "'.");
					return {};
				}

				if (right.size() > left.size())
				{
					print_error("Assignment of value type '" + String(right.type_name())
						+ "' to variable of type '" + left.type_name() + "' reduces precision.");
					return {};
				}
				break;
			}

			default:
				throw std::runtime_error("Invalid type");
		}

		return DeclarationContext(std::move(var), std::move(value));
	}

	Result<ExpressionStatementContext> validate_expression_statement(const ExpressionStatementSyntax& syntax, GlobalSymbolTable& globals, LocalSymbolTable& locals)
	{
		auto res = validate_expression(syntax.expression(), globals, locals);

		if (!res)
			return {};

		return ExpressionStatementContext(res.unwrap());
	}

	Result<BlockStatementContext> validate_block_statement(const BlockStatementSyntax& syntax, GlobalSymbolTable& globals, LocalSymbolTable& locals)
	{
		// TODO: add validation for other things

		auto success = true;

		Array<StatementContext> statements;

		for (const auto& statement : syntax.statements())
		{
			auto res = validate_statement(statement, globals, locals);
			
			success = success && res;

			if (res)
				statements.emplace_back(res.unwrap());
		}

		if (!success)
			return {};

		return BlockStatementContext(std::move(statements));
	}

	Result<StatementContext> validate_statement(const StatementSyntax& statement, GlobalSymbolTable& globals, LocalSymbolTable& locals)
	{
		switch (statement.type())
		{
			case StatementType::Declaration:
			{
				auto res = validate_declaration_statement(statement.declaration(), globals, locals);

				if (!res)
					return {};

				return StatementContext(res.unwrap());
			}

			case StatementType::Expression:
			{
				auto res = validate_expression_statement(statement.expression(), globals, locals);

				if (!res)
					return {};

				return StatementContext(res.unwrap());
			}

			case StatementType::Block:
			{
				auto res = validate_block_statement(statement.block(), globals, locals);

				if (!res)
					return {};

				return StatementContext(res.unwrap());
			}

			default:
				throw std::runtime_error("Validation for this type of statement is not implemented yet");
		}
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
		return true;
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
					containing_types.clear();
					break;

				case GlobalSymbolType::Function:
					success = success && validate_function(data.function_syntax(), globals);
					break;

				default:
					break;
			}
		}		

		if (!success)
			return {};

		return ProgramContext(globals.take_structs(), globals.take_functions());
	}
}
