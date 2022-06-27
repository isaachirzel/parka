#include <stdexcept>
#include <warbler/validator.hpp>
#include <warbler/util/print.hpp>

namespace warbler
{
	Result<ExpressionContext> validate_expression(const ExpressionSyntax& syntax, FunctionSymbolTable& symbols);

	Result<TypeAnnotationContext> validate_type_annotation(const TypeAnnotationSyntax& syntax, GlobalSymbolTable& symbol_table)
	{
		auto name = syntax.name().text();
		auto *symbol = symbol_table.resolve(name);

		if (symbol == nullptr)	// couldn't find symbol in context tree
		{
			print_error(syntax.name(), "The type '" + symbol->symbol() + "' does not exist this scope.");
			return {};
		}

		if (symbol->is_invalid())
			return {};

		AnnotationType type;

		switch (symbol->type())
		{
			case SymbolType::Struct:
				type = AnnotationType::Struct;
				break;

			case SymbolType::Primitive:
				type = AnnotationType::Primitive;
				break;

			default:
				print_error(syntax.name(), "Expected type name, found "
					+ get_symbol_type_name(symbol->type())
					+ " '" + name + "'.");
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
			if (symbol->type() == SymbolType::Struct && symbol->is_not_yet_validated())
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

			success = success && res;

			auto member = res.unwrap();
			auto result = members.emplace(member.name(), std::move(member));

			success = success && result.second;

			if (!result.second)
			{
				print_error(syntax.name(), "A member with name '" + member.name() + "' is already declared in struct '" + symbol + "'.");
				// TODO: Show previous declaration
			}
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

	Result<ParameterContext> validate_parameter(const ParameterSyntax& syntax, FunctionSymbolTable& symbols)
	{
		auto type = validate_type_annotation(syntax.type(), symbols.globals());

		if (!type)
			return {};

		return ParameterContext(syntax.name().text(), type.unwrap(), syntax.is_mutable());
	}

	Result<FunctionSignatureContext> validate_function_signature(const FunctionSignatureSyntax& syntax, FunctionSymbolTable& symbols)
	{
		auto success = true;

		Array<usize> parameter_indeces;

		for (const auto& parameter_syntax : syntax.parameters())
		{
			auto result = symbols.add_parameter(parameter_syntax);

			success = success && result.success;

			auto parameter = validate_parameter(parameter_syntax, symbols);

			success = success && parameter;

			if (!parameter)
			{
				result.data.invalidate();

				continue;
			}

			auto index = symbols.add_validated_parameter(parameter.unwrap());

			result.data.validate(index);
			parameter_indeces.push_back(index);
		}

		Optional<TypeAnnotationContext> return_type;

		if (syntax.return_type().has_value())
		{
			auto res = validate_type_annotation(syntax.return_type().value(), symbols.globals());

			success = success && res;

			if (res)
				return_type = res.unwrap();
		}

		if (!success)
			return {};		

		return FunctionSignatureContext(std::move(parameter_indeces), std::move(return_type));
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
				throw std::invalid_argument("Invalid constant type");
		}
	}

	Result<ExpressionContext> validate_symbol(const SymbolSyntax& syntax, FunctionSymbolTable& symbols)
	{
		auto symbol = syntax.token().text();
		auto *symbol_data = symbols.resolve(symbol);

		if (!symbol_data)
		{
			print_error(syntax.token(), "The symbol '" + symbol + "' could not be found in this scope.");
			return {};
		}

		if (symbol_data->type() == SymbolType::Package)
		{
			print_error("Expected valid symbol, got package '" + symbol_data->symbol() + "'.");
			return {};
		}

		return ExpressionContext(SymbolContext(symbol_data->type(), symbol_data->index()));
	}

	Result<ExpressionContext> validate_assignment(const AssignmentSyntax& syntax, FunctionSymbolTable& symbols)
	{
		auto lhs = validate_expression(syntax.lhs(), symbols);

		auto success = true;

		success = success && lhs;

		auto rhs = validate_expression(syntax.rhs(), symbols);
		
		success = success && rhs;

		if (!success)
			return {};

		// TODO: validate type of assignment

		return ExpressionContext(AssignmentContext(lhs.unwrap(), rhs.unwrap(), syntax.type()));
	}

	Result<ExpressionContext> validate_expression(const ExpressionSyntax& syntax, FunctionSymbolTable& symbols)
	{
		switch (syntax.type())
		{
			case ExpressionType::Constant:
				return validate_constant(syntax.constant());

			case ExpressionType::Symbol:
				return validate_symbol(syntax.symbol(), symbols);

			case ExpressionType::Assignment:
				return validate_assignment(syntax.assignment(), symbols);

			default:
				throw std::runtime_error("Validation of this type of expression is not implemented yet");
		}
	}

	SymbolData& validate_variable(const VariableSyntax& syntax, FunctionSymbolTable& symbols)
	{
		auto result = symbols.add_variable(syntax);
		auto& symbol_data = result.data;

		if (!result.success)
		{
			symbol_data.invalidate();
			
			return symbol_data;
		}

		if (syntax.is_auto_type())
		{
			auto index = symbols.add_validated_variable(VariableContext(symbol_data.symbol(), syntax.is_mutable()));

			symbol_data.validate(index);

			return symbol_data;
		}
			
		auto type = validate_type_annotation(syntax.type(), symbols.globals());

		if (!type)
		{
			symbol_data.invalidate();
		}
		else
		{
			auto index = symbols.add_validated_variable(VariableContext(symbol_data.symbol(), type.unwrap(), syntax.is_mutable()));

			symbol_data.validate(index);
		}

		return symbol_data;
	}

	Result<DeclarationContext> validate_declaration_statement(const DeclarationSyntax& syntax, FunctionSymbolTable& symbols)
	{
		auto& variable = validate_variable(syntax.variable(), symbols);

		if (variable.is_invalid())
			return {};

		auto value = validate_expression(syntax.value(), symbols);
		
		if (!value)
			return {};

		return DeclarationContext(variable.index(), value.unwrap());
	}

	Result<ExpressionStatementContext> validate_expression_statement(const ExpressionStatementSyntax& syntax, FunctionSymbolTable& symbols)
	{
		auto res = validate_expression(syntax.expression(), symbols);

		if (!res)
			return {};

		return ExpressionStatementContext(res.unwrap());
	}

	Result<BlockStatementContext> validate_block_statement(const BlockStatementSyntax& syntax, FunctionSymbolTable& symbols)
	{
		symbols.push_block();

		auto success = true;

		Array<StatementContext> statements;

		for (const auto& statement : syntax.statements())
		{
			auto res = validate_statement(statement, symbols);
			
			success = success && res;

			if (res)
				statements.emplace_back(res.unwrap());
		}

		symbols.pop_block();

		if (!success)
			return {};

		return BlockStatementContext(std::move(statements));
	}

	Result<StatementContext> validate_statement(const StatementSyntax& statement, FunctionSymbolTable& symbols)
	{
		switch (statement.type())
		{
			case StatementType::Declaration:
			{
				auto res = validate_declaration_statement(statement.declaration(), symbols);

				if (!res)
					return {};

				return StatementContext(res.unwrap());
			}

			case StatementType::Expression:
			{
				auto res = validate_expression_statement(statement.expression(), symbols);

				if (!res)
					return {};

				return StatementContext(res.unwrap());
			}

			case StatementType::Block:
			{
				auto res = validate_block_statement(statement.block(), symbols);

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

		FunctionSymbolTable symbols(globals);

		auto success = true;
		auto signature = validate_function_signature(syntax.signature(), symbols);

		if (!signature)
			success = false;

		auto body = validate_block_statement(syntax.body(), symbols);

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
				case SymbolType::Struct:
					success = success && validate_struct(data.struct_syntax(), globals, containing_types);
					containing_types.clear();
					break;

				case SymbolType::Function:
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
